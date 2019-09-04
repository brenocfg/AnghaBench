#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {scalar_t__ nsuffix; } ;
typedef  TYPE_1__ item ;
struct TYPE_7__ {int /*<<< orphan*/  inline_ascii_response; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITEM_get_cas (TYPE_1__*) ; 
 scalar_t__ ITEM_suffix (TYPE_1__*) ; 
 char* itoa_u32 (int,char*) ; 
 char* itoa_u64 (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ settings ; 

__attribute__((used)) static inline int make_ascii_get_suffix(char *suffix, item *it, bool return_cas, int nbytes) {
    char *p = suffix;
    if (!settings.inline_ascii_response) {
        *p = ' ';
        p++;
        if (it->nsuffix == 0) {
            *p = '0';
            p++;
        } else {
            p = itoa_u32(*((uint32_t *) ITEM_suffix(it)), p);
        }
        *p = ' ';
        p = itoa_u32(nbytes-2, p+1);
    } else {
        p = suffix;
    }
    if (return_cas) {
        *p = ' ';
        p = itoa_u64(ITEM_get_cas(it), p+1);
    }
    *p = '\r';
    *(p+1) = '\n';
    *(p+2) = '\0';
    return (p - suffix) + 2;
}