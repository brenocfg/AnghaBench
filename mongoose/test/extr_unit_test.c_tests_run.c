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

/* Variables and functions */
 int /*<<< orphan*/  RUN_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_alloc_vprintf ; 
 int /*<<< orphan*/  test_assemble_uri ; 
 int /*<<< orphan*/  test_base64 ; 
 int /*<<< orphan*/  test_basic_auth_helpers ; 
 int /*<<< orphan*/  test_buffer_limit ; 
 int /*<<< orphan*/  test_cgi ; 
 int /*<<< orphan*/  test_check_ip_acl ; 
 int /*<<< orphan*/  test_coap ; 
 int /*<<< orphan*/  test_connect_fail ; 
 int /*<<< orphan*/  test_connect_opts ; 
 int /*<<< orphan*/  test_connect_opts_error_string ; 
 int /*<<< orphan*/  test_connect_ws ; 
 int /*<<< orphan*/  test_connection_errors ; 
 int /*<<< orphan*/  test_dns_decode ; 
 int /*<<< orphan*/  test_dns_decode_truncated ; 
 int /*<<< orphan*/  test_dns_encode ; 
 int /*<<< orphan*/  test_dns_reply_encode ; 
 int /*<<< orphan*/  test_dns_resolve ; 
 int /*<<< orphan*/  test_dns_resolve_hosts ; 
 int /*<<< orphan*/  test_dns_resolve_timeout ; 
 int /*<<< orphan*/  test_dns_server ; 
 int /*<<< orphan*/  test_dns_uncompress ; 
 int /*<<< orphan*/  test_get_http_var ; 
 int /*<<< orphan*/  test_hexdump ; 
 int /*<<< orphan*/  test_hexdump_file ; 
 int /*<<< orphan*/  test_http ; 
 int /*<<< orphan*/  test_http_auth ; 
 int /*<<< orphan*/  test_http_chunk ; 
 int /*<<< orphan*/  test_http_chunk2 ; 
 int /*<<< orphan*/  test_http_dav ; 
 int /*<<< orphan*/  test_http_digest_auth ; 
 int /*<<< orphan*/  test_http_endpoints ; 
 int /*<<< orphan*/  test_http_errors ; 
 int /*<<< orphan*/  test_http_extra_headers ; 
 int /*<<< orphan*/  test_http_index ; 
 int /*<<< orphan*/  test_http_multipart ; 
 int /*<<< orphan*/  test_http_multipart2 ; 
 int /*<<< orphan*/  test_http_multipart_pipeline ; 
 int /*<<< orphan*/  test_http_multipart_upload ; 
 int /*<<< orphan*/  test_http_not_modified ; 
 int /*<<< orphan*/  test_http_parse_header ; 
 int /*<<< orphan*/  test_http_pipeline ; 
 int /*<<< orphan*/  test_http_range ; 
 int /*<<< orphan*/  test_http_rewrites ; 
 int /*<<< orphan*/  test_http_send_redirect ; 
 int /*<<< orphan*/  test_http_serve_file ; 
 int /*<<< orphan*/  test_http_serve_file_streaming ; 
 int /*<<< orphan*/  test_mbuf ; 
 int /*<<< orphan*/  test_mg_normalize_uri_path ; 
 int /*<<< orphan*/  test_mg_uri_to_local_path ; 
 int /*<<< orphan*/  test_mg_url_encode ; 
 int /*<<< orphan*/  test_mgr ; 
 int /*<<< orphan*/  test_modern_crypto ; 
 int /*<<< orphan*/  test_mqtt_broker ; 
 int /*<<< orphan*/  test_mqtt_client_keep_alive ; 
 int /*<<< orphan*/  test_mqtt_connack ; 
 int /*<<< orphan*/  test_mqtt_handshake ; 
 int /*<<< orphan*/  test_mqtt_match_topic_expression ; 
 int /*<<< orphan*/  test_mqtt_nullary ; 
 int /*<<< orphan*/  test_mqtt_parse_mqtt ; 
 int /*<<< orphan*/  test_mqtt_parse_mqtt_qos1 ; 
 int /*<<< orphan*/  test_mqtt_publish ; 
 int /*<<< orphan*/  test_mqtt_simple_acks ; 
 int /*<<< orphan*/  test_mqtt_suback ; 
 int /*<<< orphan*/  test_mqtt_subscribe ; 
 int /*<<< orphan*/  test_mqtt_unsubscribe ; 
 int /*<<< orphan*/  test_parse_address ; 
 int /*<<< orphan*/  test_parse_date_string ; 
 int /*<<< orphan*/  test_parse_http_message ; 
 int /*<<< orphan*/  test_parse_uri ; 
 int /*<<< orphan*/  test_resolve ; 
 int /*<<< orphan*/  test_simple ; 
 int /*<<< orphan*/  test_sntp ; 
 int /*<<< orphan*/  test_sock_addr_to_str ; 
 int /*<<< orphan*/  test_socketpair ; 
 int /*<<< orphan*/  test_socks ; 
 int /*<<< orphan*/  test_ssi ; 
 int /*<<< orphan*/  test_ssl ; 
 int /*<<< orphan*/  test_strcmp ; 
 int /*<<< orphan*/  test_thread ; 
 int /*<<< orphan*/  test_timer ; 
 int /*<<< orphan*/  test_to64 ; 
 int /*<<< orphan*/  test_udp ; 
 int /*<<< orphan*/  test_websocket ; 
 int /*<<< orphan*/  test_websocket_big ; 
 int /*<<< orphan*/  test_websocket_endpoint ; 

const char *tests_run(const char *filter) {
  RUN_TEST(test_mbuf);
  RUN_TEST(test_parse_uri);
  RUN_TEST(test_assemble_uri);
  RUN_TEST(test_parse_address);
  RUN_TEST(test_mg_normalize_uri_path);
  RUN_TEST(test_mg_uri_to_local_path);
  RUN_TEST(test_mg_url_encode);
  RUN_TEST(test_check_ip_acl);
  RUN_TEST(test_connect_opts);
  RUN_TEST(test_connect_opts_error_string);
  RUN_TEST(test_to64);
  RUN_TEST(test_alloc_vprintf);
  RUN_TEST(test_socketpair);
  RUN_TEST(test_timer);
#ifdef __linux__
  RUN_TEST(test_simple);
#endif
#if MG_ENABLE_THREADS
  RUN_TEST(test_thread);
#endif
  RUN_TEST(test_mgr);
  RUN_TEST(test_parse_http_message);
  RUN_TEST(test_get_http_var);
  RUN_TEST(test_http_serve_file);
  RUN_TEST(test_http_serve_file_streaming);
  RUN_TEST(test_http);
  RUN_TEST(test_http_pipeline);
  RUN_TEST(test_http_send_redirect);
  RUN_TEST(test_http_digest_auth);
  RUN_TEST(test_http_errors);
  RUN_TEST(test_http_index);
  RUN_TEST(test_http_parse_header);
  RUN_TEST(test_ssi);
#ifndef NO_CGI_TEST
  RUN_TEST(test_cgi);
#endif
  RUN_TEST(test_http_rewrites);
  RUN_TEST(test_http_dav);
  RUN_TEST(test_http_range);
  RUN_TEST(test_http_multipart);
#if MG_ENABLE_HTTP_STREAMING_MULTIPART
  RUN_TEST(test_http_multipart2);
  RUN_TEST(test_http_multipart_pipeline);
  RUN_TEST(test_http_multipart_upload);
#endif
  RUN_TEST(test_parse_date_string);
  RUN_TEST(test_websocket);
  RUN_TEST(test_websocket_endpoint);
  RUN_TEST(test_connect_ws);
  RUN_TEST(test_websocket_big);
  RUN_TEST(test_http_chunk);
  RUN_TEST(test_http_chunk2);
  RUN_TEST(test_http_not_modified);
  RUN_TEST(test_http_extra_headers);
  RUN_TEST(test_http_endpoints);
  RUN_TEST(test_mqtt_handshake);
  RUN_TEST(test_mqtt_publish);
  RUN_TEST(test_mqtt_subscribe);
  RUN_TEST(test_mqtt_unsubscribe);
  RUN_TEST(test_mqtt_connack);
  RUN_TEST(test_mqtt_suback);
  RUN_TEST(test_mqtt_simple_acks);
  RUN_TEST(test_mqtt_nullary);
  RUN_TEST(test_mqtt_parse_mqtt);
  RUN_TEST(test_mqtt_parse_mqtt_qos1);
  RUN_TEST(test_mqtt_match_topic_expression);
  RUN_TEST(test_mqtt_client_keep_alive);
#if MG_ENABLE_MQTT_BROKER
  RUN_TEST(test_mqtt_broker);
#endif
  RUN_TEST(test_dns_encode);
  RUN_TEST(test_dns_uncompress);
  RUN_TEST(test_dns_decode);
  RUN_TEST(test_dns_decode_truncated);
  RUN_TEST(test_dns_reply_encode);
#if MG_ENABLE_DNS_SERVER
  RUN_TEST(test_dns_server);
#endif
  RUN_TEST(test_dns_resolve);
  RUN_TEST(test_dns_resolve_timeout);
#ifndef NO_RESOLVE_HOSTS_TEST
  RUN_TEST(test_dns_resolve_hosts);
#endif
  RUN_TEST(test_buffer_limit);
  RUN_TEST(test_connection_errors);
  RUN_TEST(test_connect_fail);
#ifndef NO_DNS_TEST
  RUN_TEST(test_resolve);
#endif
  RUN_TEST(test_base64);
  RUN_TEST(test_sock_addr_to_str);
  RUN_TEST(test_hexdump);
  RUN_TEST(test_hexdump_file);
  RUN_TEST(test_basic_auth_helpers);
  RUN_TEST(test_http_auth);
#if MG_ENABLE_SSL
  RUN_TEST(test_ssl);
#ifdef OPENSSL_VERSION_NUMBER
  RUN_TEST(test_modern_crypto);
#endif
#endif
  RUN_TEST(test_udp);
#if MG_ENABLE_COAP
  RUN_TEST(test_coap);
#endif
#if MG_ENABLE_SNTP
  RUN_TEST(test_sntp);
#endif
  RUN_TEST(test_strcmp);
#if MG_ENABLE_SOCKS
  RUN_TEST(test_socks);
#endif
  return NULL;
}