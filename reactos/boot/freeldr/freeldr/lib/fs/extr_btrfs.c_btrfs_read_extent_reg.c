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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct btrfs_path {int dummy; } ;
struct btrfs_file_extent_item {scalar_t__ num_bytes; scalar_t__ disk_bytenr; scalar_t__ disk_num_bytes; scalar_t__ compression; scalar_t__ offset; } ;

/* Variables and functions */
 scalar_t__ ALIGN_DOWN_BY (scalar_t__,int) ; 
 scalar_t__ BTRFS_COMPRESS_NONE ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 char* FrLdrTempAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrLdrTempFree (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_ADDRESS ; 
 scalar_t__ READ_ERROR ; 
 int /*<<< orphan*/  RtlZeroMemory (char*,scalar_t__) ; 
 int SECTOR_SIZE ; 
 int /*<<< orphan*/  TAG_BTRFS_FILE ; 
 int /*<<< orphan*/  disk_read (scalar_t__,char*,scalar_t__) ; 
 scalar_t__ logical_physical (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static u64 btrfs_read_extent_reg(struct btrfs_path *path, struct btrfs_file_extent_item *extent,
                                 u64 offset, u64 size, char *out)
{
    u64 physical, dlen;
    char *temp_out;
    dlen = extent->num_bytes;

    if (offset > dlen)
    {
        ERR("Tried to read offset (%llu) beyond extent length (%lu)\n", offset, dlen);
        return READ_ERROR;
    }

    if (size > dlen - offset)
        size = dlen - offset;

    /* Handle sparse extent */
    if (extent->disk_bytenr == 0 && extent->disk_num_bytes == 0)
    {
        RtlZeroMemory(out, size);
        return size;
    }

    physical = logical_physical(extent->disk_bytenr);
    if (physical == INVALID_ADDRESS)
    {
        ERR("Unable to convert logical address to physical: %llu\n", extent->disk_bytenr);
        return READ_ERROR;
    }

    if (extent->compression == BTRFS_COMPRESS_NONE)
    {
        physical += extent->offset + offset;

        /* If somebody tried to do unaligned access */
        if (physical & (SECTOR_SIZE - 1))
        {
            u32 shift;

            temp_out = FrLdrTempAlloc(SECTOR_SIZE, TAG_BTRFS_FILE);

            if (!disk_read(ALIGN_DOWN_BY(physical, SECTOR_SIZE), temp_out, SECTOR_SIZE))
            {
                FrLdrTempFree(temp_out, TAG_BTRFS_FILE);
                return READ_ERROR;
            }

            shift = (u32)(physical & (SECTOR_SIZE - 1));

            if (size <= SECTOR_SIZE - shift)
            {
                memcpy(out, temp_out + shift, size);
                FrLdrTempFree(temp_out, TAG_BTRFS_FILE);
                return size;
            }

            memcpy(out, temp_out + shift, SECTOR_SIZE - shift);
            FrLdrTempFree(temp_out, TAG_BTRFS_FILE);

            if (!disk_read(physical + SECTOR_SIZE - shift, out + SECTOR_SIZE - shift, size - SECTOR_SIZE + shift))
                return READ_ERROR;
        } else
        {
            if (!disk_read(physical, out, size))
                return READ_ERROR;
        }

        return size;
    }

    ERR("No compression supported right now\n");
    return READ_ERROR;
}