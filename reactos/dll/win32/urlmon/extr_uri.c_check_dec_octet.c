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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL check_dec_octet(const WCHAR **ptr) {
    const WCHAR *c1, *c2, *c3;

    c1 = *ptr;
    /* A dec-octet must be at least 1 digit long. */
    if(*c1 < '0' || *c1 > '9')
        return FALSE;

    ++(*ptr);

    c2 = *ptr;
    /* Since the 1-digit requirement was met, it doesn't
     * matter if this is a DIGIT value, it's considered a
     * dec-octet.
     */
    if(*c2 < '0' || *c2 > '9')
        return TRUE;

    ++(*ptr);

    c3 = *ptr;
    /* Same explanation as above. */
    if(*c3 < '0' || *c3 > '9')
        return TRUE;

    /* Anything > 255 isn't a valid IP dec-octet. */
    if(*c1 >= '2' && *c2 >= '5' && *c3 >= '5') {
        *ptr = c1;
        return FALSE;
    }

    ++(*ptr);
    return TRUE;
}