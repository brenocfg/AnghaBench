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
typedef  int /*<<< orphan*/  npy_ucs4 ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int SMALL_STRING ; 
 int /*<<< orphan*/  _unistripw (int /*<<< orphan*/ *,int) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static char *
_uni_copy_n_strip(char *original, char *temp, int nc)
{
    if (nc*sizeof(npy_ucs4) > SMALL_STRING) {
        temp = malloc(nc*sizeof(npy_ucs4));
        if (!temp) {
            PyErr_NoMemory();
            return NULL;
        }
    }
    memcpy(temp, original, nc*sizeof(npy_ucs4));
    _unistripw((npy_ucs4 *)temp, nc);
    return temp;
}