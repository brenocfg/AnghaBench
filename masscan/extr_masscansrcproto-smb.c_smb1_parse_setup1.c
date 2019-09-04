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
struct TYPE_3__ {unsigned int byte_state; size_t byte_count; size_t byte_offset; int flags2; unsigned char unicode_char; } ;
struct TYPE_4__ {TYPE_1__ smb1; } ;
struct SMBSTUFF {TYPE_2__ hdr; } ;
struct BannerOutput {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_LEN ; 
 int /*<<< orphan*/  PROTO_SMB ; 
 int /*<<< orphan*/  banout_append (struct BannerOutput*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  banout_append_char (struct BannerOutput*,int /*<<< orphan*/ ,unsigned char const) ; 
 int /*<<< orphan*/  banout_append_unicode (struct BannerOutput*,int /*<<< orphan*/ ,unsigned char const) ; 

__attribute__((used)) static size_t
smb1_parse_setup1(struct SMBSTUFF *smb, const unsigned char *px, size_t offset, size_t max, struct BannerOutput *banout)
{
    size_t original_offset = offset;
    unsigned state = smb->hdr.smb1.byte_state;
    enum {
        D_PADDING,
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
            case D_PADDING:
                if (smb->hdr.smb1.flags2 & 0x8000) {
                    state = D_OSU1;
                } else {
                    state = D_OSA1;
                }
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