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
typedef  int /*<<< orphan*/  LZ4IO_prefs_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EXM_THROW (int,char*) ; 
 unsigned int LZ4IO_fwriteSparse (int /*<<< orphan*/ * const,int /*<<< orphan*/ *,size_t*,size_t,unsigned int) ; 
 int /*<<< orphan*/  LZ4IO_fwriteSparseEnd (int /*<<< orphan*/ *,unsigned int) ; 
 size_t const MAGICNUMBER_SIZE ; 
 int /*<<< orphan*/  PTSIZE ; 
 int PTSIZET ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 size_t fread (size_t*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t fwrite (unsigned char*,int,size_t const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long long LZ4IO_passThrough(LZ4IO_prefs_t* const prefs, FILE* finput, FILE* foutput, unsigned char MNstore[MAGICNUMBER_SIZE])
{
	size_t buffer[PTSIZET];
    size_t readBytes = 1;
    unsigned long long total = MAGICNUMBER_SIZE;
    unsigned storedSkips = 0;

    size_t const sizeCheck = fwrite(MNstore, 1, MAGICNUMBER_SIZE, foutput);
    if (sizeCheck != MAGICNUMBER_SIZE) EXM_THROW(50, "Pass-through write error");

    while (readBytes) {
        readBytes = fread(buffer, 1, PTSIZE, finput);
        total += readBytes;
        storedSkips = LZ4IO_fwriteSparse(prefs, foutput, buffer, readBytes, storedSkips);
    }
    if (ferror(finput)) EXM_THROW(51, "Read Error");

    LZ4IO_fwriteSparseEnd(foutput, storedSkips);
    return total;
}