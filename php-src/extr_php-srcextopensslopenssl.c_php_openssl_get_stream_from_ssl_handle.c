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
typedef  int /*<<< orphan*/  php_stream ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 scalar_t__ SSL_get_ex_data (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_stream_data_index ; 

php_stream* php_openssl_get_stream_from_ssl_handle(const SSL *ssl)
{
	return (php_stream*)SSL_get_ex_data(ssl, ssl_stream_data_index);
}