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
struct mg_connection {int dummy; } ;
struct http_message {int /*<<< orphan*/  body; } ;
typedef  int /*<<< orphan*/  host ;
typedef  int /*<<< orphan*/  file_name ;
typedef  int /*<<< orphan*/  file_data ;
typedef  int /*<<< orphan*/  bucket ;

/* Variables and functions */
 int /*<<< orphan*/  mg_get_http_var (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  mg_printf (struct mg_connection*,char*,char*) ; 
 int /*<<< orphan*/  send_error_result (struct mg_connection*,char*) ; 
 int /*<<< orphan*/  send_s3_request (struct mg_connection*,char*,char*,char*,char*) ; 

__attribute__((used)) static void handle_api_call(struct mg_connection *nc, struct http_message *hm) {
  char file_name[100], file_data[100], host[100], bucket[100];

  /* Get form variables */
  mg_get_http_var(&hm->body, "file_name", file_name, sizeof(file_name));
  mg_get_http_var(&hm->body, "file_data", file_data, sizeof(file_data));
  mg_get_http_var(&hm->body, "host", host, sizeof(host));
  mg_get_http_var(&hm->body, "bucket", bucket, sizeof(bucket));

  /* Send headers */
  mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");

  /* Send body */
  if (file_name[0] == '\0' || file_data[0] == '\0' || bucket[0] == '\0') {
    send_error_result(nc, "bad input");
  } else {
    send_s3_request(nc, file_name, file_data, host, bucket);
  }
}