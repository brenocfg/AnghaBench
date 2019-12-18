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
struct TYPE_7__ {unsigned int byte_state; size_t byte_count; size_t byte_offset; int flags2; unsigned char unicode_char; } ;
struct TYPE_8__ {TYPE_3__ smb1; } ;
struct TYPE_5__ {int /*<<< orphan*/  ChallengeLength; } ;
struct TYPE_6__ {TYPE_1__ negotiate; } ;
struct SMBSTUFF {TYPE_4__ hdr; TYPE_2__ parms; } ;
struct BannerOutput {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_LEN ; 
 int /*<<< orphan*/  PROTO_SMB ; 
 int /*<<< orphan*/  banout_append (struct BannerOutput*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  banout_append_char (struct BannerOutput*,int /*<<< orphan*/ ,unsigned char const) ; 
 int /*<<< orphan*/  banout_append_unicode (struct BannerOutput*,int /*<<< orphan*/ ,unsigned char const) ; 

__attribute__((used)) static size_t
smb1_parse_negotiate1(struct SMBSTUFF *smb, const unsigned char *px, size_t offset, size_t max, struct BannerOutput *banout)
{
    size_t original_offset = offset;
    unsigned state = smb->hdr.smb1.byte_state;
    enum {
        D_NEGOT_CHALLENGE,
        D_NEGOT_DOMAINA_PRE,
        D_NEGOT_NAMEA_PRE,
        D_NEGOT_DOMAINA,
        D_NEGOT_NAMEA,
        D_NEGOT_ENDA,
        D_NEGOT_DOMAINU1,
        D_NEGOT_DOMAINU2,
        D_NEGOT_DOMAIN1,
        D_NEGOT_DOMAIN2,
        D_NEGOT_NAMEU1,
        D_NEGOT_NAMEU2,
        D_NEGOT_NAME1,
        D_NEGOT_NAME2,
        D_NEGOT_END,
        
        D_UNKNOWN,
    };
    
    if (max > offset + (smb->hdr.smb1.byte_count - smb->hdr.smb1.byte_offset))
        max = offset + (smb->hdr.smb1.byte_count - smb->hdr.smb1.byte_offset);
    
    for (;offset<max; offset++)
    switch (state) {
        case D_NEGOT_CHALLENGE:
            if (smb->parms.negotiate.ChallengeLength == 0) {
                if (smb->hdr.smb1.flags2 & 0x8000) {
                    state = D_NEGOT_DOMAINU1;
                } else {
                    state = D_NEGOT_DOMAINA_PRE;
                }
                offset--;
            } else
                smb->parms.negotiate.ChallengeLength--;
            break;
        case D_NEGOT_DOMAINU1:
        case D_NEGOT_NAMEU1:
            smb->hdr.smb1.unicode_char = px[offset];
            state++;
            break;
        case D_NEGOT_DOMAINU2:
            smb->hdr.smb1.unicode_char |= px[offset]<<8;
            if (smb->hdr.smb1.unicode_char == 0) {
                state = D_NEGOT_NAMEU1;
            } else {
                banout_append(banout, PROTO_SMB, " domain=", AUTO_LEN);
                banout_append_unicode(banout, PROTO_SMB, smb->hdr.smb1.unicode_char);
                state++;
            }
            break;
        case D_NEGOT_NAMEU2:
            smb->hdr.smb1.unicode_char |= px[offset]<<8;
            if (smb->hdr.smb1.unicode_char == 0) {
                state = D_NEGOT_END;
            } else {
                banout_append(banout, PROTO_SMB, " name=", AUTO_LEN);
                banout_append_unicode(banout, PROTO_SMB, smb->hdr.smb1.unicode_char);
                state++;
            }
            break;
        case D_NEGOT_DOMAIN1:
        case D_NEGOT_NAME1:
            smb->hdr.smb1.unicode_char = px[offset];
            state++;
            break;
        case D_NEGOT_DOMAIN2:
        case D_NEGOT_NAME2:
            smb->hdr.smb1.unicode_char |= px[offset]<<8;
            if (smb->hdr.smb1.unicode_char == 0) {
                state++;
            } else {
                banout_append_unicode(banout, PROTO_SMB, smb->hdr.smb1.unicode_char);
                state--;
            }
            break;
            
        case D_NEGOT_DOMAINA_PRE:
            if (px[offset] == 0) {
                state = D_NEGOT_NAMEA_PRE;
            } else {
                banout_append(banout, PROTO_SMB, " domain=", AUTO_LEN);
                banout_append_char(banout, PROTO_SMB, px[offset]);
                state = D_NEGOT_DOMAINA;
            }
            break;
        case D_NEGOT_NAMEA_PRE:
            if (px[offset] == 0) {
                state = D_NEGOT_END;
            } else {
                banout_append(banout, PROTO_SMB, " name=", AUTO_LEN);
                banout_append_char(banout, PROTO_SMB, px[offset]);
                state = D_NEGOT_NAMEA;
            }
            break;
        case D_NEGOT_DOMAINA:
        case D_NEGOT_NAMEA:
            if (px[offset] == 0) {
                state++;
            } else {
                banout_append_char(banout, PROTO_SMB, px[offset]);
            }
            break;
            
        default:
            break;
    }
    
    smb->hdr.smb1.byte_state = (unsigned short)state;
    smb->hdr.smb1.byte_offset += (unsigned short)(offset - original_offset);
    return offset - original_offset;
}