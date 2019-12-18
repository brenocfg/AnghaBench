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
 size_t fread (char* const,int,size_t const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char* const) ; 
 scalar_t__ malloc (size_t const) ; 
 int memcmp (char* const,char* const,size_t const) ; 

__attribute__((used)) static int compare(FILE* f0, FILE* f1)
{
    int result = 0;
    const size_t tempBufferBytes = 65536;
    char* const b0 = (char*) malloc(tempBufferBytes);
    char* const b1 = (char*) malloc(tempBufferBytes);

    while(0 == result)
    {
        const size_t r0 = fread(b0, 1, tempBufferBytes, f0);
        const size_t r1 = fread(b1, 1, tempBufferBytes, f1);

        result = (int) r0 - (int) r1;

        if (0 == r0 || 0 == r1) break;
        if (0 == result) result = memcmp(b0, b1, r0);
    }

    free(b1);
    free(b0);
    return result;
}