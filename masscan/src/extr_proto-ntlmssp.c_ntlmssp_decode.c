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
struct NtlmsspDecode {size_t length; size_t offset; unsigned char* buf; } ;
struct BannerOutput {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_LEN ; 
 unsigned char* MALLOC (size_t) ; 
 int /*<<< orphan*/  PROTO_SMB ; 
 int /*<<< orphan*/  append_unicode_string (struct BannerOutput*,int /*<<< orphan*/ ,char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  banout_append (struct BannerOutput*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ memcmp (char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  sprintf_s (char*,int,char*,unsigned char const,unsigned char const,unsigned char const,unsigned char const) ; 

void
ntlmssp_decode(struct NtlmsspDecode *x,
              const unsigned char *px, size_t length,
              struct BannerOutput *banout)
{
    unsigned message_type;
    unsigned name_offset;
    unsigned name_length;
    unsigned info_offset;
    unsigned info_length;
    //unsigned flags;
    unsigned i;
    
    if (length > x->length - x->offset)
        length = x->length - x->offset;
    
    /* See if we have a fragment, in which case we need to allocate a buffer
     * to contain it */
    if (x->offset == 0 && x->length > length) {
        x->buf = MALLOC(x->length);
        memcpy(x->buf, px, length);
        x->offset = (unsigned)length;
        return;
    } else if (x->offset) {
        memcpy(x->buf + x->offset, px, length);
        x->offset += (unsigned)length;
        if (x->offset < x->length)
            return;
        
        /* now reset the input to point to our buffer instead */
        px = x->buf;
        length = x->length;
    }
    
    if (length < 56)
        goto end;
    
    /* Verify the signature. There are other protocols that we could possibly
     * detect at this point and do something else useful with, but for right now,
     * we are just doing NTLM */
    if (memcmp("NTLMSSP", px, 8) != 0)
        goto end;
    
    /* Verify this is a "challenge" packet, which has all the interesting
     * fields. */
    message_type = px[8] | px[9]<<8 | px[10]<<16 | px[11]<<24;
    if (message_type != 2)
        goto end;
    
    /* Grab the Domain field. This is a pointer in these 8 bytes here
     * that points into the payload section of the chunk */
    name_length = px[12] | px[13]<<8;
    name_offset = px[16] | px[17]<<8 | px[18]<<16 | px[19]<<24;
    if (name_length && name_length + name_offset < length) {
        append_unicode_string(banout, PROTO_SMB, "domain", px+name_offset, name_length);
    }
    
    /* Grab flags */
    //flags = px[20] | px[21]<<8 | px[22]<<16 | px[23]<<24;
    
    /* Info field */
    info_length = px[40] | px[41]<<8;
    info_offset = px[44] | px[45]<<8 | px[46]<<16 | px[47]<<24;

    /* Version field */
    {
        char buf[64];
        sprintf_s(buf, sizeof(buf), " version=%u.%u.%u ntlm-ver=%u",
                  px[48],
                  px[49],
                  px[50] | px[51]<<8,
                  px[55]
                  );
        banout_append(banout, PROTO_SMB, buf, AUTO_LEN);
    }

    /* Parse all the fields */
    for (i=info_offset; i+4<info_offset+info_length && i+4<length; ) {
        unsigned type = px[i] | px[i+1]<<8;
        size_t len = px[i+2] | px[i+3]<<8;
        i += 4;
        
        if (len > info_offset + info_length - i)
            len = info_offset + info_length - i;
        if (len > length - i)
            len = length - i;
        
        switch (type) {
            case 0x00: /* MsvAvEOL */
                i = info_offset + info_length;
                continue;
            case 1: /* MsvAvNbComputerName */
                append_unicode_string(banout, PROTO_SMB, "name", px+i, len);
                break;
            case 2: /* MsvAvNbDomainName */
                append_unicode_string(banout, PROTO_SMB, "domain", px+i, len);
                break;
            case 3: /* MsvAvDnsComputerName */
                append_unicode_string(banout, PROTO_SMB, "name-dns", px+i, len);
                break;
            case 4: /* MsvAvDnsDomainName */
                append_unicode_string(banout, PROTO_SMB, "domain-dns", px+i, len);
                break;
            case 5: /* MsvAvDnsTreeName */
                append_unicode_string(banout, PROTO_SMB, "forest", px+i, len);
                break;
            case 6: /* MsvAvFlags */
                break;
            case 7: /* MsvAvTimestamp */
                break;
            case 8: /* MsvAvSingleHost */
                break;
            case 9: /* MsvAvTargetName */
                append_unicode_string(banout, PROTO_SMB, "target", px+i, len);
                break;
            case 10: /* MsvChannelBindings */
                break;
            default:
                break;
        }
        i += (unsigned)len;
    }

    
    
    /* Grab the other fields. This*/
    
end:
    /*
     * Free the buffer if needed
     */
    if (x->buf) {
        free(x->buf);
        x->buf = 0;
    }
    
}