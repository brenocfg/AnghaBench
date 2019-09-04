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
typedef  unsigned char uint32_t ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_dump_indent (int /*<<< orphan*/ *,char const*,size_t,int) ; 
 int /*<<< orphan*/  BIO_indent (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,unsigned char,...) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  BIO_write (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 unsigned char SSL3_MT_NEWSESSION_TICKET ; 
#define  TLSEXT_TYPE_application_layer_protocol_negotiation 138 
#define  TLSEXT_TYPE_early_data 137 
#define  TLSEXT_TYPE_ec_point_formats 136 
#define  TLSEXT_TYPE_key_share 135 
#define  TLSEXT_TYPE_max_fragment_length 134 
#define  TLSEXT_TYPE_psk_kex_modes 133 
#define  TLSEXT_TYPE_renegotiate 132 
#define  TLSEXT_TYPE_session_ticket 131 
#define  TLSEXT_TYPE_signature_algorithms 130 
#define  TLSEXT_TYPE_supported_groups 129 
#define  TLSEXT_TYPE_supported_versions 128 
 int /*<<< orphan*/  ssl_exts_tbl ; 
 int /*<<< orphan*/  ssl_groups_tbl ; 
 int /*<<< orphan*/  ssl_mfl_tbl ; 
 int /*<<< orphan*/  ssl_point_tbl ; 
 int /*<<< orphan*/  ssl_print_hex (int /*<<< orphan*/ *,int,char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  ssl_psk_kex_modes_tbl ; 
 int /*<<< orphan*/  ssl_sigalg_tbl ; 
 int ssl_trace_list (int /*<<< orphan*/ *,int,unsigned char const*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_trace_str (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_version_tbl ; 

__attribute__((used)) static int ssl_print_extension(BIO *bio, int indent, int server,
                               unsigned char mt, int extype,
                               const unsigned char *ext, size_t extlen)
{
    size_t xlen, share_len;
    unsigned int sigalg;
    uint32_t max_early_data;

    BIO_indent(bio, indent, 80);
    BIO_printf(bio, "extension_type=%s(%d), length=%d\n",
               ssl_trace_str(extype, ssl_exts_tbl), extype, (int)extlen);
    switch (extype) {
    case TLSEXT_TYPE_max_fragment_length:
        if (extlen < 1)
            return 0;
        xlen = extlen;
        return ssl_trace_list(bio, indent + 2, ext, xlen, 1, ssl_mfl_tbl);

    case TLSEXT_TYPE_ec_point_formats:
        if (extlen < 1)
            return 0;
        xlen = ext[0];
        if (extlen != xlen + 1)
            return 0;
        return ssl_trace_list(bio, indent + 2, ext + 1, xlen, 1, ssl_point_tbl);

    case TLSEXT_TYPE_supported_groups:
        if (extlen < 2)
            return 0;
        xlen = (ext[0] << 8) | ext[1];
        if (extlen != xlen + 2)
            return 0;
        return ssl_trace_list(bio, indent + 2, ext + 2, xlen, 2, ssl_groups_tbl);
    case TLSEXT_TYPE_application_layer_protocol_negotiation:
        if (extlen < 2)
            return 0;
        xlen = (ext[0] << 8) | ext[1];
        if (extlen != xlen + 2)
            return 0;
        ext += 2;
        while (xlen > 0) {
            size_t plen = *ext++;

            if (plen + 1 > xlen)
                return 0;
            BIO_indent(bio, indent + 2, 80);
            BIO_write(bio, ext, plen);
            BIO_puts(bio, "\n");
            ext += plen;
            xlen -= plen + 1;
        }
        return 1;

    case TLSEXT_TYPE_signature_algorithms:

        if (extlen < 2)
            return 0;
        xlen = (ext[0] << 8) | ext[1];
        if (extlen != xlen + 2)
            return 0;
        if (xlen & 1)
            return 0;
        ext += 2;
        while (xlen > 0) {
            BIO_indent(bio, indent + 2, 80);
            sigalg = (ext[0] << 8) | ext[1];
            BIO_printf(bio, "%s (0x%04x)\n",
                       ssl_trace_str(sigalg, ssl_sigalg_tbl), sigalg);
            xlen -= 2;
            ext += 2;
        }
        break;

    case TLSEXT_TYPE_renegotiate:
        if (extlen < 1)
            return 0;
        xlen = ext[0];
        if (xlen + 1 != extlen)
            return 0;
        ext++;
        if (xlen) {
            if (server) {
                if (xlen & 1)
                    return 0;
                xlen >>= 1;
            }
            ssl_print_hex(bio, indent + 4, "client_verify_data", ext, xlen);
            if (server) {
                ext += xlen;
                ssl_print_hex(bio, indent + 4, "server_verify_data", ext, xlen);
            }
        } else {
            BIO_indent(bio, indent + 4, 80);
            BIO_puts(bio, "<EMPTY>\n");
        }
        break;

    case TLSEXT_TYPE_session_ticket:
        if (extlen != 0)
            ssl_print_hex(bio, indent + 4, "ticket", ext, extlen);
        break;

    case TLSEXT_TYPE_key_share:
        if (server && extlen == 2) {
            int group_id;

            /* We assume this is an HRR, otherwise this is an invalid key_share */
            group_id = (ext[0] << 8) | ext[1];
            BIO_indent(bio, indent + 4, 80);
            BIO_printf(bio, "NamedGroup: %s (%d)\n",
                       ssl_trace_str(group_id, ssl_groups_tbl), group_id);
            break;
        }
        if (extlen < 2)
            return 0;
        if (server) {
            xlen = extlen;
        } else {
            xlen = (ext[0] << 8) | ext[1];
            if (extlen != xlen + 2)
                return 0;
            ext += 2;
        }
        for (; xlen > 0; ext += share_len, xlen -= share_len) {
            int group_id;

            if (xlen < 4)
                return 0;
            group_id = (ext[0] << 8) | ext[1];
            share_len = (ext[2] << 8) | ext[3];
            ext += 4;
            xlen -= 4;
            if (xlen < share_len)
                return 0;
            BIO_indent(bio, indent + 4, 80);
            BIO_printf(bio, "NamedGroup: %s (%d)\n",
                       ssl_trace_str(group_id, ssl_groups_tbl), group_id);
            ssl_print_hex(bio, indent + 4, "key_exchange: ", ext, share_len);
        }
        break;

    case TLSEXT_TYPE_supported_versions:
        if (server) {
            int version;

            if (extlen != 2)
                return 0;
            version = (ext[0] << 8) | ext[1];
            BIO_indent(bio, indent + 4, 80);
            BIO_printf(bio, "%s (%d)\n",
                       ssl_trace_str(version, ssl_version_tbl), version);
            break;
        }
        if (extlen < 1)
            return 0;
        xlen = ext[0];
        if (extlen != xlen + 1)
            return 0;
        return ssl_trace_list(bio, indent + 2, ext + 1, xlen, 2,
                              ssl_version_tbl);

    case TLSEXT_TYPE_psk_kex_modes:
        if (extlen < 1)
            return 0;
        xlen = ext[0];
        if (extlen != xlen + 1)
            return 0;
        return ssl_trace_list(bio, indent + 2, ext + 1, xlen, 1,
                              ssl_psk_kex_modes_tbl);

    case TLSEXT_TYPE_early_data:
        if (mt != SSL3_MT_NEWSESSION_TICKET)
            break;
        if (extlen != 4)
            return 0;
        max_early_data = (ext[0] << 24) | (ext[1] << 16) | (ext[2] << 8)
                         | ext[3];
        BIO_indent(bio, indent + 2, 80);
        BIO_printf(bio, "max_early_data=%u\n", max_early_data);
        break;

    default:
        BIO_dump_indent(bio, (const char *)ext, extlen, indent + 2);
    }
    return 1;
}