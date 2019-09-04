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
typedef  scalar_t__ uLongf ;
typedef  int /*<<< orphan*/  gdIOCtx ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  GD2_DBG (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int Z_OK ; 
 int gdGetBuf (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdSeek (int /*<<< orphan*/ *,int) ; 
 int gdTell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gd_error (char*,...) ; 
 int uncompress (unsigned char*,scalar_t__*,unsigned char*,int) ; 

__attribute__((used)) static int _gd2ReadChunk (int offset, char *compBuf, int compSize, char *chunkBuf, uLongf * chunkLen, gdIOCtx * in)
{
	int zerr;

	if (gdTell(in) != offset) {
		GD2_DBG(gd_error("Positioning in file to %d", offset));
		gdSeek(in, offset);
	} else {
		GD2_DBG(gd_error("Already Positioned in file to %d", offset));
	}

	/* Read and uncompress an entire chunk. */
	GD2_DBG(gd_error("Reading file"));
	if (gdGetBuf(compBuf, compSize, in) != compSize) {
		return FALSE;
	}
	GD2_DBG(gd_error("Got %d bytes. Uncompressing into buffer of %d bytes", compSize, (int)*chunkLen));
	zerr = uncompress((unsigned char *) chunkBuf, chunkLen, (unsigned char *) compBuf, compSize);
	if (zerr != Z_OK) {
		GD2_DBG(gd_error("Error %d from uncompress", zerr));
		return FALSE;
	}
	GD2_DBG(gd_error("Got chunk"));

	return TRUE;
}