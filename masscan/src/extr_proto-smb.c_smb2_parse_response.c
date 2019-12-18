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
struct TYPE_3__ {unsigned int state; size_t struct_length; size_t offset; } ;
struct TYPE_4__ {TYPE_1__ smb2; } ;
struct SMBSTUFF {TYPE_2__ hdr; } ;
typedef  unsigned char const BannerOutput ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSEDPARM (unsigned char const*) ; 

__attribute__((used)) static size_t
smb2_parse_response(struct SMBSTUFF *smb, const unsigned char *px, size_t offset, size_t max, struct BannerOutput *banout)
{
    size_t original_offset = offset;
    unsigned state = smb->hdr.smb2.state;
    
    UNUSEDPARM(banout);
    UNUSEDPARM(px);

    if (max > offset + (smb->hdr.smb2.struct_length - smb->hdr.smb2.offset))
        max = offset + (smb->hdr.smb2.struct_length - smb->hdr.smb2.offset);
    
    for (;offset<max; offset++)
        switch (state) {
            default:
                break;
        }
    
    smb->hdr.smb2.state = (unsigned short)state;
    smb->hdr.smb2.offset += (unsigned short)(offset - original_offset);
    return offset - original_offset;
}