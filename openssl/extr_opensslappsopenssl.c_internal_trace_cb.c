#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int ingroup; int /*<<< orphan*/  bio; } ;
typedef  TYPE_1__ tracedata ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  CRYPTO_THREAD_ID ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BIO_snprintf (char*,int,char*,unsigned long,int /*<<< orphan*/ ) ; 
 int BIO_write (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_get_current_id () ; 
#define  OSSL_TRACE_CTRL_BEGIN 130 
#define  OSSL_TRACE_CTRL_END 129 
#define  OSSL_TRACE_CTRL_WRITE 128 
 int /*<<< orphan*/  OSSL_trace_get_category_name (int) ; 
 int /*<<< orphan*/  PREFIX_CTRL_SET_PREFIX ; 
 int /*<<< orphan*/  ossl_assert (int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static size_t internal_trace_cb(const char *buf, size_t cnt,
                                int category, int cmd, void *vdata)
{
    int ret = 0;
    tracedata *trace_data = vdata;
    union {
        CRYPTO_THREAD_ID tid;
        unsigned long ltid;
    } tid;
    char buffer[256];

    switch (cmd) {
    case OSSL_TRACE_CTRL_BEGIN:
        if (!ossl_assert(!trace_data->ingroup))
            return 0;
        trace_data->ingroup = 1;

        tid.ltid = 0;
        tid.tid = CRYPTO_THREAD_get_current_id();

        BIO_snprintf(buffer, sizeof(buffer), "TRACE[%lx]:%s: ", tid.ltid,
                     OSSL_trace_get_category_name(category));
        BIO_ctrl(trace_data->bio, PREFIX_CTRL_SET_PREFIX,
                 strlen(buffer), buffer);
        break;
    case OSSL_TRACE_CTRL_WRITE:
        if (!ossl_assert(trace_data->ingroup))
            return 0;

        ret = BIO_write(trace_data->bio, buf, cnt);
        break;
    case OSSL_TRACE_CTRL_END:
        if (!ossl_assert(trace_data->ingroup))
            return 0;
        trace_data->ingroup = 0;

        BIO_ctrl(trace_data->bio, PREFIX_CTRL_SET_PREFIX, 0, NULL);

        break;
    }

    return ret < 0 ? 0 : ret;
}