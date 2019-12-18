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
struct CertDecode {int is_capture_issuer; int is_capture_subject; } ;
struct BannerOutput {int dummy; } ;

/* Variables and functions */
 unsigned char* MALLOC (size_t) ; 
 int /*<<< orphan*/  PROTO_SSL3 ; 
 unsigned int PROTO_VULN ; 
 unsigned int PROTO_X509_CERT ; 
 int /*<<< orphan*/  banout_init (struct BannerOutput*) ; 
 int /*<<< orphan*/  banout_release (struct BannerOutput*) ; 
 unsigned char* banout_string (struct BannerOutput*,int /*<<< orphan*/ ) ; 
 size_t banout_string_length (struct BannerOutput*,int /*<<< orphan*/ ) ; 
 size_t base64_decode (unsigned char*,size_t,unsigned char*,size_t) ; 
 int /*<<< orphan*/  cndb_add (unsigned int,unsigned char const*,size_t) ; 
 char* cndb_lookup (unsigned int) ; 
 int /*<<< orphan*/  found_type (unsigned char const*,size_t) ; 
 scalar_t__ memcmp (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  x509_decode (struct CertDecode*,unsigned char*,size_t,struct BannerOutput*) ; 
 int /*<<< orphan*/  x509_decode_init (struct CertDecode*,size_t) ; 

void
readscan_report(  unsigned ip,
                  unsigned app_proto,
                  unsigned char **r_data,
                  size_t *r_data_length)
{
    size_t data_length = *r_data_length;
    unsigned char *data = *r_data;


    if (app_proto == PROTO_X509_CERT) {
        unsigned char *der = MALLOC(data_length);
        struct CertDecode x;
        size_t der_length;
        struct BannerOutput banout[1];
        const unsigned char *banner;
        size_t banner_length;

        banout_init(banout);

        der_length = base64_decode(der, data_length, data, data_length);
        
        x509_decode_init(&x, data_length);
        x.is_capture_issuer = 1;
        x.is_capture_subject = 1;
        x509_decode(&x, der, der_length, banout);

        banner = banout_string(banout, PROTO_SSL3);
        banner_length = banout_string_length(banout, PROTO_SSL3);

        if (banner_length) {
            if (!found_type(banner, banner_length))
                cndb_add(ip, banner, banner_length);
        }

        banout_release(banout);
    /*} else if (0 && app_proto == PROTO_SSL3) {
        cndb_add(ip, data, data_length);*/
    } else if (app_proto == PROTO_VULN) {
        const char *name = cndb_lookup(ip);
        
        if (data_length == 15 && memcmp(data, "SSL[heartbeat] ", 15) == 0)
            return;

        if (name && strlen(name) < 300) {
            //printf("vuln=%s\n", name);
            ((char*)data)[data_length] = ' ';
            memcpy((char*)data+data_length+1, name, strlen(name)+1);
            data_length += strlen(name)+1;
        }

        /* kludge */
        if (data_length == 31 && memcmp(data, "SSL[heartbeat] SSL[HEARTBLEED] ", 31) == 0)
            return;
    }

}