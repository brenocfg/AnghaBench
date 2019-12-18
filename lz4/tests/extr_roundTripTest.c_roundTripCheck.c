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

/* Variables and functions */
 size_t LZ4_compressBound (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (void* const) ; 
 void* malloc (size_t const) ; 
 int /*<<< orphan*/  roundTripTest (void* const,size_t const,void* const,size_t const,void const*,size_t,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void roundTripCheck(const void* srcBuff, size_t srcSize, int clevel)
{
    size_t const cBuffSize = LZ4_compressBound((int)srcSize);
    void* const cBuff = malloc(cBuffSize);
    void* const rBuff = malloc(cBuffSize);

    if (!cBuff || !rBuff) {
        fprintf(stderr, "not enough memory ! \n");
        exit(1);
    }

    roundTripTest(rBuff, cBuffSize,
                  cBuff, cBuffSize,
                  srcBuff, srcSize,
                  clevel);

    free(rBuff);
    free(cBuff);
}