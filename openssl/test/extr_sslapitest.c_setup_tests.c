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
 int /*<<< orphan*/  ADD_ALL_TESTS (int /*<<< orphan*/  (*) (int),int) ; 
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_get_alloc_counts (int*,int*,int*) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_error (char*) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ ) ; 
 int TOTAL_SSL_SET_BIO_TESTS ; 
 int /*<<< orphan*/ * cert ; 
 int /*<<< orphan*/  certsdir ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 int /*<<< orphan*/  max_fragment_len_test ; 
 int /*<<< orphan*/ * privkey ; 
 int /*<<< orphan*/  shared_ciphers_data ; 
 int /*<<< orphan*/  srpvfile ; 
 int /*<<< orphan*/  test_ca_names (int) ; 
 int /*<<< orphan*/  test_cert_cb (int) ; 
 int /*<<< orphan*/  test_ciphersuite_change ; 
 int /*<<< orphan*/  test_client_cert_cb (int) ; 
 int /*<<< orphan*/  test_client_hello_cb ; 
 int /*<<< orphan*/  test_custom_exts (int) ; 
 int /*<<< orphan*/  test_early_data_not_expected (int) ; 
 int /*<<< orphan*/  test_early_data_not_sent (int) ; 
 int /*<<< orphan*/  test_early_data_psk (int) ; 
 int /*<<< orphan*/  test_early_data_read_write (int) ; 
 int /*<<< orphan*/  test_early_data_replay (int) ; 
 int /*<<< orphan*/  test_early_data_skip (int) ; 
 int /*<<< orphan*/  test_early_data_skip_abort (int) ; 
 int /*<<< orphan*/  test_early_data_skip_hrr (int) ; 
 int /*<<< orphan*/  test_early_data_skip_hrr_fail (int) ; 
 int /*<<< orphan*/  test_early_data_tls1_2 (int) ; 
 int /*<<< orphan*/  test_export_key_mat (int) ; 
 int /*<<< orphan*/  test_export_key_mat_early (int) ; 
 int /*<<< orphan*/  test_get_argument (int) ; 
 int /*<<< orphan*/  test_info_callback (int) ; 
 int /*<<< orphan*/  test_key_exchange (int) ; 
 int /*<<< orphan*/  test_key_update ; 
 int /*<<< orphan*/  test_key_update_in_write (int) ; 
 int /*<<< orphan*/  test_keylog ; 
 int /*<<< orphan*/  test_keylog_no_master_key ; 
 int /*<<< orphan*/  test_ktls_client_no_rx_server ; 
 int /*<<< orphan*/  test_ktls_client_no_tx_server ; 
 int /*<<< orphan*/  test_ktls_client_no_txrx_server ; 
 int /*<<< orphan*/  test_ktls_client_server ; 
 int /*<<< orphan*/  test_ktls_no_rx_client_no_rx_server ; 
 int /*<<< orphan*/  test_ktls_no_rx_client_no_tx_server ; 
 int /*<<< orphan*/  test_ktls_no_rx_client_no_txrx_server ; 
 int /*<<< orphan*/  test_ktls_no_rx_client_server ; 
 int /*<<< orphan*/  test_ktls_no_tx_client_no_rx_server ; 
 int /*<<< orphan*/  test_ktls_no_tx_client_no_tx_server ; 
 int /*<<< orphan*/  test_ktls_no_tx_client_no_txrx_server ; 
 int /*<<< orphan*/  test_ktls_no_tx_client_server ; 
 int /*<<< orphan*/  test_ktls_no_txrx_client_no_rx_server ; 
 int /*<<< orphan*/  test_ktls_no_txrx_client_no_tx_server ; 
 int /*<<< orphan*/  test_ktls_no_txrx_client_no_txrx_server ; 
 int /*<<< orphan*/  test_ktls_no_txrx_client_server ; 
 int /*<<< orphan*/  test_ktls_sendfile ; 
 int /*<<< orphan*/  test_large_message_dtls ; 
 int /*<<< orphan*/  test_large_message_tls ; 
 int /*<<< orphan*/  test_large_message_tls_read_ahead ; 
 int /*<<< orphan*/  test_max_fragment_len_ext (int) ; 
 void* test_mk_file_path (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_no_ems ; 
 int /*<<< orphan*/  test_pha_key_update ; 
 int /*<<< orphan*/  test_printf_stdout (char*,int,int,int) ; 
 int /*<<< orphan*/  test_psk_tickets ; 
 int /*<<< orphan*/  test_serverinfo (int) ; 
 int /*<<< orphan*/  test_session_with_both_cache ; 
 int /*<<< orphan*/  test_session_with_only_ext_cache ; 
 int /*<<< orphan*/  test_session_with_only_int_cache ; 
 int /*<<< orphan*/  test_set_ciphersuite (int) ; 
 int /*<<< orphan*/  test_set_sigalgs (int) ; 
 int /*<<< orphan*/  test_shutdown (int) ; 
 int /*<<< orphan*/  test_srp (int) ; 
 int /*<<< orphan*/  test_ssl_bio_change_rbio ; 
 int /*<<< orphan*/  test_ssl_bio_change_wbio ; 
 int /*<<< orphan*/  test_ssl_bio_pop_next_bio ; 
 int /*<<< orphan*/  test_ssl_bio_pop_ssl_bio ; 
 int /*<<< orphan*/  test_ssl_clear (int) ; 
 int /*<<< orphan*/  test_ssl_get_shared_ciphers (int) ; 
 int /*<<< orphan*/  test_ssl_pending (int) ; 
 int /*<<< orphan*/  test_ssl_set_bio (int) ; 
 int /*<<< orphan*/  test_stateful_tickets (int) ; 
 int /*<<< orphan*/  test_stateless ; 
 int /*<<< orphan*/  test_stateless_tickets (int) ; 
 int /*<<< orphan*/  test_ticket_callbacks (int) ; 
 int /*<<< orphan*/  test_tls13_ciphersuite (int) ; 
 int /*<<< orphan*/  test_tls13_psk (int) ; 
 int /*<<< orphan*/  test_tlsext_status_type ; 
 int /*<<< orphan*/  testsigalgs ; 
 int /*<<< orphan*/  tmpfilename ; 

int setup_tests(void)
{
    if (!TEST_ptr(certsdir = test_get_argument(0))
            || !TEST_ptr(srpvfile = test_get_argument(1))
            || !TEST_ptr(tmpfilename = test_get_argument(2)))
        return 0;

    if (getenv("OPENSSL_TEST_GETCOUNTS") != NULL) {
#ifdef OPENSSL_NO_CRYPTO_MDEBUG
        TEST_error("not supported in this build");
        return 0;
#else
        int i, mcount, rcount, fcount;

        for (i = 0; i < 4; i++)
            test_export_key_mat(i);
        CRYPTO_get_alloc_counts(&mcount, &rcount, &fcount);
        test_printf_stdout("malloc %d realloc %d free %d\n",
                mcount, rcount, fcount);
        return 1;
#endif
    }

    cert = test_mk_file_path(certsdir, "servercert.pem");
    if (cert == NULL)
        return 0;

    privkey = test_mk_file_path(certsdir, "serverkey.pem");
    if (privkey == NULL) {
        OPENSSL_free(cert);
        return 0;
    }

#if !defined(OPENSSL_NO_TLS1_2) && !defined(OPENSSL_NO_KTLS) \
    && !defined(OPENSSL_NO_SOCK)
    ADD_TEST(test_ktls_no_txrx_client_no_txrx_server);
    ADD_TEST(test_ktls_no_rx_client_no_txrx_server);
    ADD_TEST(test_ktls_no_tx_client_no_txrx_server);
    ADD_TEST(test_ktls_client_no_txrx_server);
    ADD_TEST(test_ktls_no_txrx_client_no_rx_server);
    ADD_TEST(test_ktls_no_rx_client_no_rx_server);
    ADD_TEST(test_ktls_no_tx_client_no_rx_server);
    ADD_TEST(test_ktls_client_no_rx_server);
    ADD_TEST(test_ktls_no_txrx_client_no_tx_server);
    ADD_TEST(test_ktls_no_rx_client_no_tx_server);
    ADD_TEST(test_ktls_no_tx_client_no_tx_server);
    ADD_TEST(test_ktls_client_no_tx_server);
    ADD_TEST(test_ktls_no_txrx_client_server);
    ADD_TEST(test_ktls_no_rx_client_server);
    ADD_TEST(test_ktls_no_tx_client_server);
    ADD_TEST(test_ktls_client_server);
    ADD_TEST(test_ktls_sendfile);
#endif
    ADD_TEST(test_large_message_tls);
    ADD_TEST(test_large_message_tls_read_ahead);
#ifndef OPENSSL_NO_DTLS
    ADD_TEST(test_large_message_dtls);
#endif
#ifndef OPENSSL_NO_OCSP
    ADD_TEST(test_tlsext_status_type);
#endif
    ADD_TEST(test_session_with_only_int_cache);
    ADD_TEST(test_session_with_only_ext_cache);
    ADD_TEST(test_session_with_both_cache);
#ifndef OPENSSL_NO_TLS1_3
    ADD_ALL_TESTS(test_stateful_tickets, 3);
    ADD_ALL_TESTS(test_stateless_tickets, 3);
    ADD_TEST(test_psk_tickets);
#endif
    ADD_ALL_TESTS(test_ssl_set_bio, TOTAL_SSL_SET_BIO_TESTS);
    ADD_TEST(test_ssl_bio_pop_next_bio);
    ADD_TEST(test_ssl_bio_pop_ssl_bio);
    ADD_TEST(test_ssl_bio_change_rbio);
    ADD_TEST(test_ssl_bio_change_wbio);
#if !defined(OPENSSL_NO_TLS1_2) || defined(OPENSSL_NO_TLS1_3)
    ADD_ALL_TESTS(test_set_sigalgs, OSSL_NELEM(testsigalgs) * 2);
    ADD_TEST(test_keylog);
#endif
#ifndef OPENSSL_NO_TLS1_3
    ADD_TEST(test_keylog_no_master_key);
#endif
#ifndef OPENSSL_NO_TLS1_2
    ADD_TEST(test_client_hello_cb);
    ADD_TEST(test_no_ems);
#endif
#ifndef OPENSSL_NO_TLS1_3
    ADD_ALL_TESTS(test_early_data_read_write, 3);
    /*
     * We don't do replay tests for external PSK. Replay protection isn't used
     * in that scenario.
     */
    ADD_ALL_TESTS(test_early_data_replay, 2);
    ADD_ALL_TESTS(test_early_data_skip, 3);
    ADD_ALL_TESTS(test_early_data_skip_hrr, 3);
    ADD_ALL_TESTS(test_early_data_skip_hrr_fail, 3);
    ADD_ALL_TESTS(test_early_data_skip_abort, 3);
    ADD_ALL_TESTS(test_early_data_not_sent, 3);
    ADD_ALL_TESTS(test_early_data_psk, 8);
    ADD_ALL_TESTS(test_early_data_not_expected, 3);
# ifndef OPENSSL_NO_TLS1_2
    ADD_ALL_TESTS(test_early_data_tls1_2, 3);
# endif
#endif
#ifndef OPENSSL_NO_TLS1_3
    ADD_ALL_TESTS(test_set_ciphersuite, 10);
    ADD_TEST(test_ciphersuite_change);
    ADD_ALL_TESTS(test_tls13_ciphersuite, 4);
# ifdef OPENSSL_NO_PSK
    ADD_ALL_TESTS(test_tls13_psk, 1);
# else
    ADD_ALL_TESTS(test_tls13_psk, 4);
# endif  /* OPENSSL_NO_PSK */
# ifndef OPENSSL_NO_TLS1_2
    /* Test with both TLSv1.3 and 1.2 versions */
    ADD_ALL_TESTS(test_key_exchange, 14);
# else
    /* Test with only TLSv1.3 versions */
    ADD_ALL_TESTS(test_key_exchange, 12);
# endif
    ADD_ALL_TESTS(test_custom_exts, 5);
    ADD_TEST(test_stateless);
    ADD_TEST(test_pha_key_update);
#else
    ADD_ALL_TESTS(test_custom_exts, 3);
#endif
    ADD_ALL_TESTS(test_serverinfo, 8);
    ADD_ALL_TESTS(test_export_key_mat, 6);
#ifndef OPENSSL_NO_TLS1_3
    ADD_ALL_TESTS(test_export_key_mat_early, 3);
    ADD_TEST(test_key_update);
    ADD_ALL_TESTS(test_key_update_in_write, 2);
#endif
    ADD_ALL_TESTS(test_ssl_clear, 2);
    ADD_ALL_TESTS(test_max_fragment_len_ext, OSSL_NELEM(max_fragment_len_test));
#if !defined(OPENSSL_NO_SRP) && !defined(OPENSSL_NO_TLS1_2)
    ADD_ALL_TESTS(test_srp, 6);
#endif
    ADD_ALL_TESTS(test_info_callback, 6);
    ADD_ALL_TESTS(test_ssl_pending, 2);
    ADD_ALL_TESTS(test_ssl_get_shared_ciphers, OSSL_NELEM(shared_ciphers_data));
    ADD_ALL_TESTS(test_ticket_callbacks, 12);
    ADD_ALL_TESTS(test_shutdown, 7);
    ADD_ALL_TESTS(test_cert_cb, 6);
    ADD_ALL_TESTS(test_client_cert_cb, 2);
    ADD_ALL_TESTS(test_ca_names, 3);
    return 1;
}