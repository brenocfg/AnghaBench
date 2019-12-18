#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  endifW ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  char PRUnichar ;
typedef  int /*<<< orphan*/  HTMLDocumentNode ;
typedef  int DWORD ;

/* Variables and functions */
 int IE_MAJOR_VERSION ; 
 int IE_MINOR_VERSION ; 
 char* heap_alloc (int) ; 
 scalar_t__ isdigitW (char const) ; 
 scalar_t__ isspaceW (char const) ; 
 scalar_t__ memcmp (char const*,char const*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlenW (char const*) ; 

__attribute__((used)) static PRUnichar *handle_insert_comment(HTMLDocumentNode *doc, const PRUnichar *comment)
{
    int majorv = 0, minorv = 0;
    const PRUnichar *ptr, *end;
    PRUnichar *buf;
    DWORD len;

    enum {
        CMP_EQ,
        CMP_LT,
        CMP_LTE,
        CMP_GT,
        CMP_GTE
    } cmpt = CMP_EQ;

    static const PRUnichar endifW[] = {'<','!','[','e','n','d','i','f',']'};

    if(comment[0] != '[' || comment[1] != 'i' || comment[2] != 'f')
        return NULL;

    ptr = comment+3;
    while(isspaceW(*ptr))
        ptr++;

    if(ptr[0] == 'l' && ptr[1] == 't') {
        ptr += 2;
        if(*ptr == 'e') {
            cmpt = CMP_LTE;
            ptr++;
        }else {
            cmpt = CMP_LT;
        }
    }else if(ptr[0] == 'g' && ptr[1] == 't') {
        ptr += 2;
        if(*ptr == 'e') {
            cmpt = CMP_GTE;
            ptr++;
        }else {
            cmpt = CMP_GT;
        }
    }

    if(!isspaceW(*ptr++))
        return NULL;
    while(isspaceW(*ptr))
        ptr++;

    if(ptr[0] != 'I' || ptr[1] != 'E')
        return NULL;

    ptr +=2;
    if(!isspaceW(*ptr++))
        return NULL;
    while(isspaceW(*ptr))
        ptr++;

    if(!isdigitW(*ptr))
        return NULL;
    while(isdigitW(*ptr))
        majorv = majorv*10 + (*ptr++ - '0');

    if(*ptr == '.') {
        ptr++;
        if(!isdigitW(*ptr))
            return NULL;
        while(isdigitW(*ptr))
            minorv = minorv*10 + (*ptr++ - '0');
    }

    while(isspaceW(*ptr))
        ptr++;
    if(ptr[0] != ']' || ptr[1] != '>')
        return NULL;
    ptr += 2;

    len = strlenW(ptr);
    if(len < sizeof(endifW)/sizeof(WCHAR))
        return NULL;

    end = ptr + len-sizeof(endifW)/sizeof(WCHAR);
    if(memcmp(end, endifW, sizeof(endifW)))
        return NULL;

    switch(cmpt) {
    case CMP_EQ:
        if(majorv == IE_MAJOR_VERSION && minorv == IE_MINOR_VERSION)
            break;
        return NULL;
    case CMP_LT:
        if(majorv > IE_MAJOR_VERSION)
            break;
        if(majorv == IE_MAJOR_VERSION && minorv > IE_MINOR_VERSION)
            break;
        return NULL;
    case CMP_LTE:
        if(majorv > IE_MAJOR_VERSION)
            break;
        if(majorv == IE_MAJOR_VERSION && minorv >= IE_MINOR_VERSION)
            break;
        return NULL;
    case CMP_GT:
        if(majorv < IE_MAJOR_VERSION)
            break;
        if(majorv == IE_MAJOR_VERSION && minorv < IE_MINOR_VERSION)
            break;
        return NULL;
    case CMP_GTE:
        if(majorv < IE_MAJOR_VERSION)
            break;
        if(majorv == IE_MAJOR_VERSION && minorv <= IE_MINOR_VERSION)
            break;
        return NULL;
    }

    buf = heap_alloc((end-ptr+1)*sizeof(WCHAR));
    if(!buf)
        return NULL;

    memcpy(buf, ptr, (end-ptr)*sizeof(WCHAR));
    buf[end-ptr] = 0;

    return buf;
}