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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 size_t fwrite (void*,size_t,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void safe_fwrite(void* buf, size_t eltSize, size_t nbElt, FILE* f)
{
    size_t const writtenSize = fwrite(buf, eltSize, nbElt, f);
    size_t const expectedSize = eltSize * nbElt;
    if (nbElt>0) assert(expectedSize / nbElt == eltSize);  /* check overflow */
    if (writtenSize < expectedSize) {
        if (ferror(f))  /* note : ferror() must follow fwrite */
            fprintf(stderr, "Write failed \n");
        else
            fprintf(stderr, "Write too short \n");
        exit(1);
    }
}