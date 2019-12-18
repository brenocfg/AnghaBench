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
 int /*<<< orphan*/  INLINE_FILE_TAG ; 
 int /*<<< orphan*/  __wrap_buffer_read_from_file ; 
 int /*<<< orphan*/  __wrap_buffer_write_file ; 
 int /*<<< orphan*/  expect_string (int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  pem ; 
 int test_client_key ; 
 int /*<<< orphan*/  test_server_key ; 
 int /*<<< orphan*/  tls_crypt_v2_write_client_key_file (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  will_return (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
test_tls_crypt_v2_write_client_key_file(void **state) {
    const char *filename = "testfilename.key";

    /* Test writing the client key */
    expect_string(__wrap_buffer_write_file, filename, filename);
    expect_string(__wrap_buffer_write_file, pem, test_client_key);
    will_return(__wrap_buffer_write_file, true);

    /* Key generation re-reads the created file as a sanity check */
    expect_string(__wrap_buffer_read_from_file, filename, filename);
    will_return(__wrap_buffer_read_from_file, test_client_key);

    tls_crypt_v2_write_client_key_file(filename, NULL, INLINE_FILE_TAG,
                                       test_server_key);
}