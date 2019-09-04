#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_7__ {unsigned int byte_state; size_t byte_count; size_t byte_offset; int flags2; unsigned char unicode_char; } ;
struct TYPE_8__ {TYPE_3__ smb1; } ;
struct TYPE_5__ {size_t BlobOffset; size_t BlobLength; } ;
struct TYPE_6__ {TYPE_1__ setup; } ;
struct SMBSTUFF {TYPE_4__ hdr; TYPE_2__ parms; int /*<<< orphan*/  spnego; } ;
struct BannerOutput {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_LEN ; 
 int /*<<< orphan*/  PROTO_SMB ; 
 int /*<<< orphan*/  banout_append (struct BannerOutput*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  banout_append_char (struct BannerOutput*,int /*<<< orphan*/ ,unsigned char const) ; 
 int /*<<< orphan*/  banout_append_unicode (struct BannerOutput*,int /*<<< orphan*/ ,unsigned char const) ; 
 int /*<<< orphan*/  spnego_decode (int /*<<< orphan*/ *,unsigned char const*,size_t,struct BannerOutput*) ; 
 int /*<<< orphan*/  spnego_decode_init (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static size_t
smb1_parse_setup2(struct SMBSTUFF *smb, const unsigned char *px, size_t offset, size_t max, struct BannerOutput *banout)
{
    size_t original_offset = offset;
    unsigned state = smb->hdr.smb1.byte_state;
    enum {
        D_BLOB,
        D_PADDING,
        D_PADDING2,
        D_OSA1,
        D_OSA2,
        D_VERSIONA1,
        D_VERSIONA2,
        D_DOMAINA1,
        D_DOMAINA2,
        D_ENDA,
        
        D_OSU1,
        D_OSU2,
        D_OSU3,
        D_OSU4,
        D_VERSION1,
        D_VERSION2,
        D_VERSION3,
        D_VERSION4,
        D_DOMAIN1,
        D_DOMAIN2,
        D_DOMAIN3,
        D_DOMAIN4,
        
        D_UNKNOWN,
    };
    
    if (max > offset + (smb->hdr.smb1.byte_count - smb->hdr.smb1.byte_offset))
        max = offset + (smb->hdr.smb1.byte_count - smb->hdr.smb1.byte_offset);
    
    for (;offset<max; offset++) {
        
        switch (state) {
            case D_BLOB:
                if (smb->parms.setup.BlobOffset == 0) {
                    spnego_decode_init(&smb->spnego, smb->parms.setup.BlobLength);
                }
            {
                size_t new_max = max;
                if (new_max > offset + smb->parms.setup.BlobLength - smb->parms.setup.BlobOffset)
                    new_max = offset + smb->parms.setup.BlobLength - smb->parms.setup.BlobOffset;
                spnego_decode(&smb->spnego, px+offset, new_max-offset, banout);
                
                smb->parms.setup.BlobOffset += (uint16_t)(new_max-offset);
                offset = new_max;
                if (smb->parms.setup.BlobLength - smb->parms.setup.BlobOffset == 0) {
                    offset--;
                    state = D_PADDING;
                }
            }
                break;
            case D_PADDING:
                /* If the blog length is odd, then there is no padding. Otherwise,
                 * there is one byte of padding */
                //if (smb->parms.setup.BlobLength & 1)
                    offset--;
                state = D_PADDING2;
                break;
            case D_PADDING2:
                if (smb->hdr.smb1.flags2 & 0x8000) {
                    state = D_OSU1;
                } else {
                    state = D_OSA1;
                }
                offset--;
                break;
            case D_OSA1:
                if (px[offset] == 0)
                    state = D_VERSIONA1;
                else {
                    banout_append(banout, PROTO_SMB, " os=", AUTO_LEN);
                    banout_append_char(banout, PROTO_SMB, px[offset]);
                    state = D_OSA2;
                }
                break;
            case D_OSA2:
                if (px[offset] == 0)
                    state = D_VERSIONA1;
                else
                    banout_append_char(banout, PROTO_SMB, px[offset]);
                break;
                
            case D_VERSIONA1:
                if (px[offset] == 0)
                    state = D_DOMAINA1;
                else {
                    banout_append(banout, PROTO_SMB, " ver=", AUTO_LEN);
                    banout_append_char(banout, PROTO_SMB, px[offset]);
                    state = D_VERSIONA2;
                }
                break;
            case D_VERSIONA2:
                if (px[offset] == 0)
                    state = D_DOMAINA1;
                else
                    banout_append_char(banout, PROTO_SMB, px[offset]);
                break;
            case D_DOMAINA1:
                if (px[offset] == 0)
                    state = D_UNKNOWN;
                else {
                    banout_append(banout, PROTO_SMB, " domain=", AUTO_LEN);
                    banout_append_char(banout, PROTO_SMB, px[offset]);
                    state = D_DOMAINA2;
                }
                break;
            case D_DOMAINA2:
                if (px[offset] == 0)
                    state = D_UNKNOWN;
                else
                    banout_append_char(banout, PROTO_SMB, px[offset]);
                break;
                
            case D_OSU1:
            case D_OSU3:
            case D_VERSION1:
            case D_VERSION3:
            case D_DOMAIN1:
            case D_DOMAIN3:
                smb->hdr.smb1.unicode_char = px[offset];
                state++;
                break;
                
            case D_OSU2:
                smb->hdr.smb1.unicode_char |= px[offset]<<8;
                if (smb->hdr.smb1.unicode_char == 0)
                    state = D_VERSION1;
                else {
                    banout_append(banout, PROTO_SMB, " os=", AUTO_LEN);
                    banout_append_unicode(banout, PROTO_SMB, smb->hdr.smb1.unicode_char);
                    state = D_OSU3;
                }
                break;
                
            case D_OSU4:
                smb->hdr.smb1.unicode_char |= px[offset]<<8;
                if (smb->hdr.smb1.unicode_char == 0)
                    state = D_VERSION1;
                else {
                    banout_append_unicode(banout, PROTO_SMB, smb->hdr.smb1.unicode_char);
                    state--;
                }
                break;
                
                
            case D_VERSION2:
                smb->hdr.smb1.unicode_char |= px[offset]<<8;
                if (smb->hdr.smb1.unicode_char == 0)
                    state = D_DOMAIN1;
                else {
                    banout_append(banout, PROTO_SMB, " ver=", AUTO_LEN);
                    banout_append_unicode(banout, PROTO_SMB, smb->hdr.smb1.unicode_char);
                    state = D_VERSION3;
                }
                break;
                
            case D_VERSION4:
                smb->hdr.smb1.unicode_char |= px[offset]<<8;
                if (smb->hdr.smb1.unicode_char == 0)
                    state = D_DOMAIN1;
                else {
                    banout_append_unicode(banout, PROTO_SMB, smb->hdr.smb1.unicode_char);
                    state--;
                }
                break;
                
            case D_DOMAIN2:
                smb->hdr.smb1.unicode_char |= px[offset]<<8;
                if (smb->hdr.smb1.unicode_char == 0)
                    state = D_UNKNOWN;
                else {
                    banout_append(banout, PROTO_SMB, " domain=", AUTO_LEN);
                    banout_append_unicode(banout, PROTO_SMB, smb->hdr.smb1.unicode_char);
                    state = D_DOMAIN3;
                }
                break;
                
            case D_DOMAIN4:
                smb->hdr.smb1.unicode_char |= px[offset]<<8;
                if (smb->hdr.smb1.unicode_char == 0)
                    state = D_UNKNOWN;
                else {
                    banout_append_unicode(banout, PROTO_SMB, smb->hdr.smb1.unicode_char);
                    state--;
                }
                break;
            default:
                break;
        }
    }
    
    smb->hdr.smb1.byte_state = (unsigned short)state;
    smb->hdr.smb1.byte_offset += (unsigned short)(offset - original_offset);
    return offset - original_offset;
}