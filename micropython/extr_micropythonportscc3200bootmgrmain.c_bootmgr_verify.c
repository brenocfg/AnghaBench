#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  _u8 ;
typedef  scalar_t__ _u32 ;
typedef  int /*<<< orphan*/  _i32 ;
struct TYPE_3__ {int FileLen; } ;
typedef  TYPE_1__ SlFsFileInfo_t ;

/* Variables and functions */
 scalar_t__ BOOTMGR_BUFF_SIZE ; 
 int /*<<< orphan*/  BOOTMGR_HASH_ALGO ; 
 int BOOTMGR_HASH_SIZE ; 
 int /*<<< orphan*/  CRYPTOHASH_SHAMD5Read (int*) ; 
 int /*<<< orphan*/  CRYPTOHASH_SHAMD5Start (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CRYPTOHASH_SHAMD5Update (int*,scalar_t__) ; 
 int /*<<< orphan*/  FS_MODE_OPEN_READ ; 
 int* bootmgr_file_buf ; 
 int /*<<< orphan*/ * bootmgr_hash_buf ; 
 int /*<<< orphan*/  sl_FsClose (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sl_FsGetInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ sl_FsOpen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sl_FsRead (int /*<<< orphan*/ ,scalar_t__,int*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

__attribute__((used)) static bool bootmgr_verify (_u8 *image) {
    SlFsFileInfo_t FsFileInfo;
    _u32 reqlen, offset = 0;
    _i32 fHandle;

    // open the file for reading
    if (0 == sl_FsOpen(image, FS_MODE_OPEN_READ, NULL, &fHandle)) {
        // get the file size
        sl_FsGetInfo(image, 0, &FsFileInfo);

        if (FsFileInfo.FileLen > BOOTMGR_HASH_SIZE) {
            FsFileInfo.FileLen -= BOOTMGR_HASH_SIZE;
            CRYPTOHASH_SHAMD5Start(BOOTMGR_HASH_ALGO, FsFileInfo.FileLen);
            do {
                if ((FsFileInfo.FileLen - offset) > BOOTMGR_BUFF_SIZE) {
                    reqlen = BOOTMGR_BUFF_SIZE;
                }
                else {
                    reqlen = FsFileInfo.FileLen - offset;
                }

                offset += sl_FsRead(fHandle, offset, bootmgr_file_buf, reqlen);
                CRYPTOHASH_SHAMD5Update(bootmgr_file_buf, reqlen);
            } while (offset < FsFileInfo.FileLen);

            CRYPTOHASH_SHAMD5Read (bootmgr_file_buf);

            // convert the resulting hash to hex
            for (_u32 i = 0; i < (BOOTMGR_HASH_SIZE / 2); i++) {
                snprintf ((char *)&bootmgr_hash_buf[(i * 2)], 3, "%02x", bootmgr_file_buf[i]);
            }

            // read the hash from the file and close it
            sl_FsRead(fHandle, offset, bootmgr_file_buf, BOOTMGR_HASH_SIZE);
            sl_FsClose (fHandle, NULL, NULL, 0);
            bootmgr_file_buf[BOOTMGR_HASH_SIZE] = '\0';
            // compare both hashes
            if (!strcmp((const char *)bootmgr_hash_buf, (const char *)bootmgr_file_buf)) {
                // it's a match
                return true;
            }
        }
        // close the file
        sl_FsClose(fHandle, NULL, NULL, 0);
    }
    return false;
}