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
 int /*<<< orphan*/  __wrap_buffer_write_file ; 
 int /*<<< orphan*/  expect_string (int /*<<< orphan*/ ,char const*,char const*) ; 
 char const* pem ; 
 char const* test_server_key ; 
 int /*<<< orphan*/  tls_crypt_v2_write_server_key_file (char const*) ; 
 int /*<<< orphan*/  will_return (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
test_tls_crypt_v2_write_server_key_file(void **state) {
    const char *filename = "testfilename.key";

    expect_string(__wrap_buffer_write_file, filename, filename);
    expect_string(__wrap_buffer_write_file, pem, test_server_key);
    will_return(__wrap_buffer_write_file, true);

    tls_crypt_v2_write_server_key_file(filename);
}