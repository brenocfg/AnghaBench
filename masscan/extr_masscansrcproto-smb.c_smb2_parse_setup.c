#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int state; size_t struct_length; size_t offset; unsigned char blob_offset; unsigned char blob_length; } ;
struct TYPE_4__ {TYPE_1__ smb2; } ;
struct SMBSTUFF {TYPE_2__ hdr; } ;
struct BannerOutput {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSEDPARM (struct BannerOutput*) ; 

__attribute__((used)) static size_t
smb2_parse_setup(struct SMBSTUFF *smb, const unsigned char *px, size_t offset, size_t max, struct BannerOutput *banout)
{
    size_t original_offset = offset;
    unsigned state = smb->hdr.smb2.state;
    
    /*
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |          Buffer Code          |           Flags               |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |        Sec Blob Offset        |        Sec Blob Length        |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     | Sec Blob
     +-+-+-+-+...
     */
    enum {
        N_FLAGS1, N_FLAGS2,
        N_BLOB_OFFSET1, N_BLOB_OFFSET2,
        N_BLOB_LENGTH1, N_BLOB_LENGTH2,

    };

    UNUSEDPARM(banout);

    if (max > offset + (smb->hdr.smb2.struct_length - smb->hdr.smb2.offset))
        max = offset + (smb->hdr.smb2.struct_length - smb->hdr.smb2.offset);
    
    for (;offset<max; offset++)
        switch (state) {
            case N_FLAGS1: case N_FLAGS2:
                state++;
                break;
            case N_BLOB_OFFSET1:
                smb->hdr.smb2.blob_offset = px[offset];
                state++;
                break;
            case N_BLOB_OFFSET2:
                smb->hdr.smb2.blob_offset |= (px[offset]<<8);
                state++;
                break;
            case N_BLOB_LENGTH1:
                smb->hdr.smb2.blob_length = px[offset];
                state++;
                break;
            case N_BLOB_LENGTH2:
                smb->hdr.smb2.blob_length |= (px[offset]<<8);
                state++;
                break;
            default:
                break;
        }
    
    smb->hdr.smb2.state = (unsigned short)state;
    smb->hdr.smb2.offset += (unsigned short)(offset - original_offset);
    return offset - original_offset;
}