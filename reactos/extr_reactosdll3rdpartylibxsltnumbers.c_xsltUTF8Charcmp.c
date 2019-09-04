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
typedef  int /*<<< orphan*/  xmlChar ;

/* Variables and functions */
 int xmlStrncmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int xmlUTF8Strsize (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
xsltUTF8Charcmp(xmlChar *utf1, xmlChar *utf2) {
    int len = xmlUTF8Strsize(utf1, 1);

    if (len < 1)
        return -1;
    if (utf1 == NULL ) {
        if (utf2 == NULL)
            return 0;
        return -1;
    }
    return xmlStrncmp(utf1, utf2, len);
}