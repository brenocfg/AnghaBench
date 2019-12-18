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
typedef  unsigned int GifWord ;
typedef  int /*<<< orphan*/  GifFileType ;

/* Variables and functions */
 int GIF_ERROR ; 
 int GIF_OK ; 
 int READ (int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static int
DGifGetWord(GifFileType * GifFile,
            GifWord *Word) {

    unsigned char c[2];

    if (READ(GifFile, c, 2) != 2) {
        return GIF_ERROR;
    }

    *Word = (((unsigned int)c[1]) << 8) + c[0];
    return GIF_OK;
}