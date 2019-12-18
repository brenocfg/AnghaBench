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
typedef  int /*<<< orphan*/  GifRecordType ;
typedef  int /*<<< orphan*/  GifFileType ;
typedef  int GifByteType ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENSION_RECORD_TYPE ; 
 int GIF_ERROR ; 
 int GIF_OK ; 
 int /*<<< orphan*/  IMAGE_DESC_RECORD_TYPE ; 
 int READ (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  TERMINATE_RECORD_TYPE ; 
 int /*<<< orphan*/  UNDEFINED_RECORD_TYPE ; 

__attribute__((used)) static int
DGifGetRecordType(GifFileType * GifFile,
                  GifRecordType * Type) {

    GifByteType Buf;

    if (READ(GifFile, &Buf, 1) != 1) {
        /* Wine-specific behavior: Native accepts broken GIF files that have no
         * terminator, so we match this by treating EOF as a terminator. */
        *Type = TERMINATE_RECORD_TYPE;
        return GIF_OK;
    }

    switch (Buf) {
      case ',':
          *Type = IMAGE_DESC_RECORD_TYPE;
          break;
      case '!':
          *Type = EXTENSION_RECORD_TYPE;
          break;
      case ';':
          *Type = TERMINATE_RECORD_TYPE;
          break;
      default:
          *Type = UNDEFINED_RECORD_TYPE;
          return GIF_ERROR;
    }

    return GIF_OK;
}