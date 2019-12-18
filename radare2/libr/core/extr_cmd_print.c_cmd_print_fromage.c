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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  RX509Certificate ;
typedef  int /*<<< orphan*/  RStrBuf ;
typedef  int /*<<< orphan*/  RCore ;
typedef  int /*<<< orphan*/  RCMS ;
typedef  int /*<<< orphan*/  RASN1Object ;

/* Variables and functions */
 int /*<<< orphan*/  asn1_setformat (int) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  help_msg_pF ; 
 int /*<<< orphan*/ * r_asn1_create_object (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  r_asn1_free_object (int /*<<< orphan*/ *) ; 
 char* r_asn1_to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cons_printf (char*,char*) ; 
 int /*<<< orphan*/  r_core_cmd_help (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* r_pkcs7_cms_to_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_pkcs7_free_cms (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_pkcs7_parse_cms (int /*<<< orphan*/  const*,int) ; 
 char* r_protobuf_decode (int /*<<< orphan*/  const*,int,int) ; 
 char* r_strbuf_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_strbuf_new (char*) ; 
 int /*<<< orphan*/  r_x509_certificate_dump (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_x509_free_certificate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_x509_parse_certificate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cmd_print_fromage(RCore *core, const char *input, const ut8* data, int size) {
	switch (*input) {
	case 'a':
		{
			asn1_setformat (input[1] != 'q');
			RASN1Object *asn1 = r_asn1_create_object (data, size, data);
			if (asn1) {
				char *res = r_asn1_to_string (asn1, 0, NULL);
				r_asn1_free_object (asn1);
				if (res) {
					r_cons_printf ("%s\n", res);
					free (res);
				}
			} else {
				eprintf ("Malformed object: did you supply enough data?\ntry to change the block size (see b?)\n");
			}
		}
		break;
	case 'x': // "pFx" x509
		{
			RX509Certificate* x509 = r_x509_parse_certificate (r_asn1_create_object (data, size, data));
			if (x509) {
				RStrBuf *sb = r_strbuf_new ("");
				r_x509_certificate_dump (x509, NULL, sb);
				char *res = r_strbuf_drain (sb);
				if (res) {
					r_cons_printf ("%s\n", res);
					free (res);
				}
				r_x509_free_certificate (x509);
			} else {
				eprintf ("Malformed object: did you supply enough data?\ntry to change the block size (see b?)\n");
			}
		}
		break;
	case 'p': // "pFp"
		{
			RCMS *cms = r_pkcs7_parse_cms (data, size);
			if (cms) {
				char *res = r_pkcs7_cms_to_string (cms);
				if (res) {
					r_cons_printf ("%s\n", res);
					free (res);
				}
				r_pkcs7_free_cms (cms);
			} else {
				eprintf ("Malformed object: did you supply enough data?\ntry to change the block size (see b?)\n");
			}
		}
		break;
	case 'b': // "pFb"
		{
			char *s = r_protobuf_decode(data, size, input[1] == 'v');
			if (s) {
				r_cons_printf ("%s", s);
				free (s);
			}
		}
		break;
	default:
	case '?': // "pF?"
		r_core_cmd_help (core, help_msg_pF);
		break;
	}
}