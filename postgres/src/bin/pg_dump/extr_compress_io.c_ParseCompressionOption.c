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
typedef  int /*<<< orphan*/  CompressionAlgorithm ;

/* Variables and functions */
 int /*<<< orphan*/  COMPR_ALG_LIBZ ; 
 int /*<<< orphan*/  COMPR_ALG_NONE ; 
 int Z_DEFAULT_COMPRESSION ; 
 int /*<<< orphan*/  fatal (char*,int) ; 

__attribute__((used)) static void
ParseCompressionOption(int compression, CompressionAlgorithm *alg, int *level)
{
	if (compression == Z_DEFAULT_COMPRESSION ||
		(compression > 0 && compression <= 9))
		*alg = COMPR_ALG_LIBZ;
	else if (compression == 0)
		*alg = COMPR_ALG_NONE;
	else
	{
		fatal("invalid compression code: %d", compression);
		*alg = COMPR_ALG_NONE;	/* keep compiler quiet */
	}

	/* The level is just the passed-in value. */
	if (level)
		*level = compression;
}