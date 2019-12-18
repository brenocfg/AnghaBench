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
typedef  int /*<<< orphan*/  operationMode_e ;

/* Variables and functions */
 char const* LZ4_EXTENSION ; 
 int /*<<< orphan*/  om_compress ; 
 int /*<<< orphan*/  om_decompress ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static operationMode_e determineOpMode(const char* inputFilename)
{
    size_t const inSize  = strlen(inputFilename);
    size_t const extSize = strlen(LZ4_EXTENSION);
    size_t const extStart= (inSize > extSize) ? inSize-extSize : 0;
    if (!strcmp(inputFilename+extStart, LZ4_EXTENSION)) return om_decompress;
    else return om_compress;
}