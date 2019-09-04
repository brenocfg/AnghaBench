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
struct stream_lavf_params {char* useragent; char* cookies_file; char* tls_ca_file; char* tls_cert_file; char* tls_key_file; scalar_t__ timeout; char* http_proxy; int /*<<< orphan*/  avopts; scalar_t__* http_header_fields; scalar_t__ referrer; scalar_t__ tls_verify; scalar_t__ cookies_enabled; } ;
struct mpv_global {int dummy; } ;
struct mp_log {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 
 char* cookies_lavf (void*,struct mp_log*,char*) ; 
 struct stream_lavf_params* mp_get_config_group (void*,struct mpv_global*,int /*<<< orphan*/ *) ; 
 char* mp_get_user_path (void*,struct mpv_global*,char*) ; 
 int /*<<< orphan*/  mp_set_avdict (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,long long) ; 
 int /*<<< orphan*/  stream_lavf_conf ; 
 scalar_t__ strlen (char*) ; 
 char* talloc_asprintf_append (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 void* talloc_new (int /*<<< orphan*/ *) ; 
 char* talloc_strdup (void*,char*) ; 

void mp_setup_av_network_options(AVDictionary **dict, struct mpv_global *global,
                                 struct mp_log *log)
{
    void *temp = talloc_new(NULL);
    struct stream_lavf_params *opts =
        mp_get_config_group(temp, global, &stream_lavf_conf);

    // HTTP specific options (other protocols ignore them)
    if (opts->useragent)
        av_dict_set(dict, "user_agent", opts->useragent, 0);
    if (opts->cookies_enabled) {
        char *file = opts->cookies_file;
        if (file && file[0])
            file = mp_get_user_path(temp, global, file);
        char *cookies = cookies_lavf(temp, log, file);
        if (cookies && cookies[0])
            av_dict_set(dict, "cookies", cookies, 0);
    }
    av_dict_set(dict, "tls_verify", opts->tls_verify ? "1" : "0", 0);
    if (opts->tls_ca_file)
        av_dict_set(dict, "ca_file", opts->tls_ca_file, 0);
    if (opts->tls_cert_file)
        av_dict_set(dict, "cert_file", opts->tls_cert_file, 0);
    if (opts->tls_key_file)
        av_dict_set(dict, "key_file", opts->tls_key_file, 0);
    char *cust_headers = talloc_strdup(temp, "");
    if (opts->referrer) {
        cust_headers = talloc_asprintf_append(cust_headers, "Referer: %s\r\n",
                                              opts->referrer);
    }
    if (opts->http_header_fields) {
        for (int n = 0; opts->http_header_fields[n]; n++) {
            cust_headers = talloc_asprintf_append(cust_headers, "%s\r\n",
                                                  opts->http_header_fields[n]);
        }
    }
    if (strlen(cust_headers))
        av_dict_set(dict, "headers", cust_headers, 0);
    av_dict_set(dict, "icy", "1", 0);
    // So far, every known protocol uses microseconds for this
    if (opts->timeout > 0) {
        char buf[80];
        snprintf(buf, sizeof(buf), "%lld", (long long)(opts->timeout * 1e6));
        av_dict_set(dict, "timeout", buf, 0);
    }
    if (opts->http_proxy && opts->http_proxy[0])
        av_dict_set(dict, "http_proxy", opts->http_proxy, 0);

    mp_set_avdict(dict, opts->avopts);

    talloc_free(temp);
}