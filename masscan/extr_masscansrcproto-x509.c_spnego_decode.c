#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  buf; } ;
struct SpnegoDecode {TYPE_3__ ntlmssp; struct CertDecode* x509; } ;
struct TYPE_6__ {unsigned char length_of_length; unsigned char remaining; } ;
struct TYPE_9__ {TYPE_1__ tag; } ;
struct TYPE_7__ {scalar_t__* remainings; scalar_t__ depth; } ;
struct CertDecode {unsigned int state; int brother_state; int child_state; int is_der_failure; TYPE_5__ u; TYPE_2__ stack; } ;
struct BannerOutput {int dummy; } ;

/* Variables and functions */
 unsigned int ASN1_pop (struct CertDecode*) ; 
 int /*<<< orphan*/  ASN1_push (struct CertDecode*,int,unsigned char) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntlmssp_decode (TYPE_3__*,unsigned char const*,size_t,struct BannerOutput*) ; 
 int /*<<< orphan*/  ntlmssp_decode_init (TYPE_3__*,scalar_t__) ; 

void
spnego_decode(struct SpnegoDecode *spnego,
            const unsigned char *px, size_t length,
            struct BannerOutput *banout)
{
    struct CertDecode *x = spnego->x509;
    unsigned i;
    unsigned state = x->state;
    
    enum {
        /*NegotiationToken ::= CHOICE {
            negTokenInit    [0] NegTokenInit,
            negTokenResp    [1] NegTokenResp
        }*/
        NegotiationToken_tag, len, lenlen,
        
        NegTokenInit_tag,
        NegTokenInit_choice,
        NegTokenResp_tag,
        NegTokenResp_choice,
        mechType_tag,
        
        negState_tag,
        supportedMech_tag,
        responseToken_tag,
        mechListMIC_tag,
        
        mechTypes_tag,
        reqFlags_tag,
        mechToken_tag,
        
        mechToken_content,
        responseToken_content,
        mechToken_content2,
        responseToken_content2,

        UnknownContents,
        
        
    };
    
#define GOTO_ERROR(state, i, length) (state)=0xFFFFFFFF;(i)=(length);continue
    
    /* 'for all bytes in the current fragment ...'
     *   'process that byte, causing a state-transition '
     */
    for (i=0; i<length; i++) {
        
        
        /*
         * If we've reached the end of the current field, then we need to
         * pop up the stack and resume parsing the parent field. Since we
         * reach the end of several levels simultaneously, we may need to
         * pop several levels at once
         */
        while (x->stack.remainings[0] == 0) {
            if (x->stack.depth == 0)
                return;
            state = ASN1_pop(x);
        }
        
        /*
         * Decrement the current 'remaining' length field.
         */
        x->stack.remainings[0]--;
        
        /*
         * Jump to the current current state
         */
        switch (state) {
            case NegotiationToken_tag:
                x->brother_state = UnknownContents;
                switch (px[i]) {
                    case 0xa0:
                        x->child_state = NegTokenInit_tag;
                        break;
                    case 0xa1:
                        x->child_state = NegTokenResp_tag;
                        break;
                    case 0x60:
                        x->child_state = mechType_tag;
                        break;
                    default:
                        x->child_state = UnknownContents;
                        break;
                }
                state = len;
                break;
                
            case NegTokenResp_choice:
                /*
                 NegTokenResp ::= SEQUENCE {
                 negState       [0] ENUMERATED {
                    accept-completed    (0),
                    accept-incomplete   (1),
                    reject              (2),
                    request-mic         (3)
                    }                                 OPTIONAL,
                 -- REQUIRED in the first reply from the target
                 supportedMech   [1] MechType      OPTIONAL,
                 -- present only in the first reply from the target
                 responseToken   [2] OCTET STRING  OPTIONAL,
                 mechListMIC     [3] OCTET STRING  OPTIONAL,
                 ...
                 }*/
                x->brother_state = NegTokenResp_choice;
                switch (px[i]) {
                    case 0xa0:
                        x->child_state = negState_tag;
                        break;
                    case 0xa1:
                        x->child_state = supportedMech_tag;
                        break;
                    case 0xa2:
                        x->child_state = responseToken_tag;
                        break;
                    case 0xa3:
                        x->child_state = mechListMIC_tag;
                        break;
                    default:
                        x->child_state = UnknownContents;
                        break;
                }
                state = len;
                break;
                
            case NegTokenResp_tag:
                if (px[i] != 0x30) {
                    x->brother_state = UnknownContents;
                    x->child_state = UnknownContents;
                } else {
                    x->brother_state = UnknownContents;
                    x->child_state = NegTokenResp_choice;
                }
                state = len;
                break;
                
            case NegTokenInit_choice:
                /*
                 NegTokenInit ::= SEQUENCE {
                 mechTypes       [0] MechTypeList,
                 reqFlags        [1] ContextFlags  OPTIONAL,
                 -- inherited from RFC 2478 for backward compatibility,
                 -- RECOMMENDED to be left out
                 mechToken       [2] OCTET STRING  OPTIONAL,
                 mechListMIC     [3] OCTET STRING  OPTIONAL,
                 ...
                 }
                 }*/
                x->brother_state = NegTokenInit_choice;
                switch (px[i]) {
                    case 0xa0:
                        x->child_state = mechTypes_tag;
                        break;
                    case 0xa1:
                        x->child_state = reqFlags_tag;
                        break;
                    case 0xa2:
                        x->child_state = mechToken_tag;
                        break;
                    case 0xa3:
                        x->child_state = mechListMIC_tag;
                        break;
                    default:
                        x->child_state = UnknownContents;
                        break;
                }
                state = len;
                break;
            
            case NegTokenInit_tag:
                if (px[i] != 0x30) {
                    x->brother_state = UnknownContents;
                    x->child_state = UnknownContents;
                } else {
                    x->brother_state = UnknownContents;
                    x->child_state = NegTokenInit_choice;
                }
                state = len;
                break;

            case mechType_tag:
                if (px[i] == 0x06) {
                    x->brother_state = NegotiationToken_tag;
                    x->child_state = UnknownContents;
                } else {
                    x->brother_state = NegotiationToken_tag;
                    x->child_state = UnknownContents;
                }
                state = len;
                break;
            
            case negState_tag:
            case supportedMech_tag:
            case mechListMIC_tag:
            case mechTypes_tag:
            case reqFlags_tag:
                x->brother_state = UnknownContents;
                x->child_state = UnknownContents;
                state = len;
                break;
            
            case responseToken_tag:
                x->brother_state = UnknownContents;
                x->child_state = responseToken_content;
                state = len;
                break;
                
            case mechToken_tag:
                x->brother_state = UnknownContents;
                x->child_state = mechToken_content;
                state = len;
                break;
            
            case mechToken_content:
            case mechToken_content2:
                break;
             
                /************************************************************************
                 ************************************************************************
                 ************************************************************************
                 ************************************************************************
                 ************************************************************************
                 ************************************************************************
                 ************************************************************************
                 */
            case responseToken_content:
                ntlmssp_decode_init(&spnego->ntlmssp, x->stack.remainings[0] + 1);
                state = responseToken_content2;
                /* fall through */
            case responseToken_content2:
            {
                size_t new_max = length - i;
                
                if (new_max > x->stack.remainings[0] + 1U)
                    new_max = x->stack.remainings[0] + 1;
                
                ntlmssp_decode(&spnego->ntlmssp, px+i, new_max, banout);
                
                x->stack.remainings[0] -= (unsigned short)(new_max - 1);
                if (x->stack.remainings[0] == 0) {
                    if (spnego->ntlmssp.buf)
                        free(spnego->ntlmssp.buf);
                }
            }
                break;
                
            case len:
                /* We do the same processing for all the various length fields.
                 * There are three possible length fields:
                 * 0x7F - for lengths 127 and below
                 * 0x81 XX - for lengths 127 to 255
                 * 0x82 XX XX - for length 256 to 65535
                 * This state processes the first byte, and if it's an extended
                 * field, switches to the correspondign xxx_LENLEN state
                 */
                if (px[i] & 0x80) {
                    x->u.tag.length_of_length = px[i]&0x7F;
                    x->u.tag.remaining = 0;
                    state = lenlen;
                    break;
                } else {
                    x->u.tag.remaining = px[i];
                    ASN1_push(x, x->brother_state, x->u.tag.remaining);
                    state = x->child_state;
                    memset(&x->u, 0, sizeof(x->u));
                    break;
                }
                break;
            case lenlen:
                /* We process all multibyte lengths the same way in this
                 * state.
                 */
                
                /* [ASN1-DER-LENGTH]
                 * Check for strict DER compliance, which says that there should
                 * be no leading zero bytes */
                if (x->u.tag.remaining == 0 && px[i] == 0)
                    x->is_der_failure = 1;
                
                /* parse this byte */
                x->u.tag.remaining = (x->u.tag.remaining)<<8 | px[i];
                x->u.tag.length_of_length--;
                
                /* If we aren't finished yet, loop around and grab the next */
                if (x->u.tag.length_of_length)
                    continue;
                
                /* [ASN1-DER-LENGTH]
                 * Check for strict DER compliance, which says that for lengths
                 * 127 and below, we need only 1 byte to encode it, not many */
                if (x->u.tag.remaining < 128)
                    x->is_der_failure = 1;
                
                /*
                 * We have finished parsing the tag-length fields, and are now
                 * ready to parse the 'value'. Push the current state on the
                 * stack, then decend into the child field.
                 */
                ASN1_push(x, x->brother_state, x->u.tag.remaining);
                state = x->child_state;
                memset(&x->u, 0, sizeof(x->u));
                break;
            default:
                ;
        }
    }
}