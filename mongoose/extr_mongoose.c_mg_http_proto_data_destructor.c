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
struct mg_http_proto_data {int /*<<< orphan*/  reverse_proxy_data; int /*<<< orphan*/  endpoints; int /*<<< orphan*/  mp_stream; int /*<<< orphan*/  cgi; int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  MG_FREE (void*) ; 
 int /*<<< orphan*/  mg_http_free_proto_data_cgi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_http_free_proto_data_endpoints (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_http_free_proto_data_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_http_free_proto_data_mp_stream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_http_free_reverse_proxy_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mg_http_proto_data_destructor(void *proto_data) {
  struct mg_http_proto_data *pd = (struct mg_http_proto_data *) proto_data;
#if MG_ENABLE_FILESYSTEM
  mg_http_free_proto_data_file(&pd->file);
#endif
#if MG_ENABLE_HTTP_CGI
  mg_http_free_proto_data_cgi(&pd->cgi);
#endif
#if MG_ENABLE_HTTP_STREAMING_MULTIPART
  mg_http_free_proto_data_mp_stream(&pd->mp_stream);
#endif
  mg_http_free_proto_data_endpoints(&pd->endpoints);
  mg_http_free_reverse_proxy_data(&pd->reverse_proxy_data);
  MG_FREE(proto_data);
}