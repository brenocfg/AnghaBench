#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  value; } ;
struct TYPE_5__ {struct TYPE_5__* next; void const* index; void* arg; int /*<<< orphan*/  handfn; } ;
typedef  TYPE_1__ THREAD_EVENT_HANDLER ;
typedef  int /*<<< orphan*/  OSSL_thread_stop_handler_fn ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  int /*<<< orphan*/  CRYPTO_THREAD_LOCAL ;

/* Variables and functions */
 int /*<<< orphan*/  FIPS_get_provider (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_CTX_THREAD_EVENT_HANDLER_INDEX ; 
 TYPE_1__* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  c_thread_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ destructor_key ; 
 TYPE_1__** init_get_thread_local (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * openssl_ctx_get_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_ctx_thread_stop ; 
 int /*<<< orphan*/  thread_event_ossl_ctx_method ; 

int ossl_init_thread_start(const void *index, void *arg,
                           OSSL_thread_stop_handler_fn handfn)
{
    THREAD_EVENT_HANDLER **hands;
    THREAD_EVENT_HANDLER *hand;
#ifdef FIPS_MODE
    OPENSSL_CTX *ctx = arg;

    /*
     * In FIPS mode the list of THREAD_EVENT_HANDLERs is unique per combination
     * of OPENSSL_CTX and thread. This is because in FIPS mode each OPENSSL_CTX
     * gets informed about thread stop events individually.
     */
    CRYPTO_THREAD_LOCAL *local
        = openssl_ctx_get_data(ctx, OPENSSL_CTX_THREAD_EVENT_HANDLER_INDEX,
                               &thread_event_ossl_ctx_method);
#else
    /*
     * Outside of FIPS mode the list of THREAD_EVENT_HANDLERs is unique per
     * thread, but may hold multiple OPENSSL_CTXs. We only get told about
     * thread stop events globally, so we have to ensure all affected
     * OPENSSL_CTXs are informed.
     */
    CRYPTO_THREAD_LOCAL *local = &destructor_key.value;
#endif

    hands = init_get_thread_local(local, 1, 0);
    if (hands == NULL)
        return 0;

#ifdef FIPS_MODE
    if (*hands == NULL) {
        /*
         * We've not yet registered any handlers for this thread. We need to get
         * libcrypto to tell us about later thread stop events. c_thread_start
         * is a callback to libcrypto defined in fipsprov.c
         */
        if (!c_thread_start(FIPS_get_provider(ctx), ossl_ctx_thread_stop))
            return 0;
    }
#endif

    hand = OPENSSL_malloc(sizeof(*hand));
    if (hand == NULL)
        return 0;

    hand->handfn = handfn;
    hand->arg = arg;
    hand->index = index;
    hand->next = *hands;
    *hands = hand;

    return 1;
}