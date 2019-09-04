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
typedef  scalar_t__ npy_ucs4 ;
typedef  int npy_intp ;

/* Variables and functions */
 int PyArray_CompareUCS4 (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_MIN (int,int) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 

__attribute__((used)) static int
_myunincmp(npy_ucs4 *s1, npy_ucs4 *s2, int len1, int len2)
{
    npy_ucs4 *sptr;
    npy_ucs4 *s1t=s1, *s2t=s2;
    int val;
    npy_intp size;
    int diff;

    if ((npy_intp)s1 % sizeof(npy_ucs4) != 0) {
        size = len1*sizeof(npy_ucs4);
        s1t = malloc(size);
        memcpy(s1t, s1, size);
    }
    if ((npy_intp)s2 % sizeof(npy_ucs4) != 0) {
        size = len2*sizeof(npy_ucs4);
        s2t = malloc(size);
        memcpy(s2t, s2, size);
    }
    val = PyArray_CompareUCS4(s1t, s2t, PyArray_MIN(len1,len2));
    if ((val != 0) || (len1 == len2)) {
        goto finish;
    }
    if (len2 > len1) {
        sptr = s2t+len1;
        val = -1;
        diff = len2-len1;
    }
    else {
        sptr = s1t+len2;
        val = 1;
        diff=len1-len2;
    }
    while (diff--) {
        if (*sptr != 0) {
            goto finish;
        }
        sptr++;
    }
    val = 0;

 finish:
    if (s1t != s1) {
        free(s1t);
    }
    if (s2t != s2) {
        free(s2t);
    }
    return val;
}