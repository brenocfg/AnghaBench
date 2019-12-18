#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct priv {int do_deint; TYPE_1__* opts; scalar_t__ num_buffers; scalar_t__* buffers; int /*<<< orphan*/  context; int /*<<< orphan*/  display; int /*<<< orphan*/  config; } ;
struct mp_filter {struct priv* priv; } ;
typedef  int /*<<< orphan*/  param ;
typedef  int /*<<< orphan*/  VAStatus ;
typedef  size_t VAProcFilterType ;
struct TYPE_7__ {size_t type; scalar_t__ algorithm; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ VAProcFilterParameterBufferDeinterlacing ;
struct TYPE_8__ {scalar_t__ type; } ;
typedef  TYPE_3__ VAProcFilterCapDeinterlacing ;
typedef  scalar_t__ VAProcDeinterlacingType ;
typedef  int /*<<< orphan*/  VAContextID ;
typedef  int /*<<< orphan*/  VAConfigID ;
typedef  scalar_t__ VABufferID ;
struct TYPE_6__ {int deint_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_VA_STATUS (struct mp_filter*,char*) ; 
 int MP_ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct mp_filter*,char*,scalar_t__) ; 
 int /*<<< orphan*/  MP_WARN (struct mp_filter*,char*) ; 
 int /*<<< orphan*/  VAEntrypointVideoProc ; 
 int VAProcDeinterlacingCount ; 
 int VAProcFilterCount ; 
 size_t VAProcFilterDeinterlacing ; 
 int /*<<< orphan*/  VAProfileNone ; 
 scalar_t__ VA_INVALID_ID ; 
 scalar_t__* deint_algorithm ; 
 int /*<<< orphan*/  vaCreateConfig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vaCreateContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vaQueryVideoProcFilters (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int*) ; 
 scalar_t__ va_create_filter_buffer (struct mp_filter*,int,int,TYPE_2__*) ; 
 int va_query_filter_caps (struct mp_filter*,size_t,TYPE_3__*,int) ; 

__attribute__((used)) static bool initialize(struct mp_filter *vf)
{
    struct priv *p = vf->priv;
    VAStatus status;

    VAConfigID config;
    status = vaCreateConfig(p->display, VAProfileNone, VAEntrypointVideoProc,
                            NULL, 0, &config);
    if (!CHECK_VA_STATUS(vf, "vaCreateConfig()")) // no entrypoint for video porc
        return false;
    p->config = config;

    VAContextID context;
    status = vaCreateContext(p->display, p->config, 0, 0, 0, NULL, 0, &context);
    if (!CHECK_VA_STATUS(vf, "vaCreateContext()"))
        return false;
    p->context = context;

    VAProcFilterType filters[VAProcFilterCount];
    int num_filters = VAProcFilterCount;
    status = vaQueryVideoProcFilters(p->display, p->context, filters, &num_filters);
    if (!CHECK_VA_STATUS(vf, "vaQueryVideoProcFilters()"))
        return false;

    VABufferID buffers[VAProcFilterCount];
    for (int i = 0; i < VAProcFilterCount; i++)
        buffers[i] = VA_INVALID_ID;
    for (int i = 0; i < num_filters; i++) {
        if (filters[i] == VAProcFilterDeinterlacing) {
            VAProcFilterCapDeinterlacing caps[VAProcDeinterlacingCount];
            int num = va_query_filter_caps(vf, VAProcFilterDeinterlacing, caps,
                                           VAProcDeinterlacingCount);
            if (!num)
                continue;
            if (p->opts->deint_type < 0) {
                for (int n = MP_ARRAY_SIZE(deint_algorithm) - 1; n > 0; n--) {
                    for (int x = 0; x < num; x++) {
                        if (caps[x].type == deint_algorithm[n]) {
                            p->opts->deint_type = n;
                            MP_VERBOSE(vf, "Selected deinterlacing algorithm: "
                                       "%d\n", deint_algorithm[n]);
                            goto found;
                        }
                    }
                }
                found: ;
            }
            if (p->opts->deint_type <= 0)
                continue;
            VAProcDeinterlacingType algorithm =
                deint_algorithm[p->opts->deint_type];
            for (int n=0; n < num; n++) { // find the algorithm
                if (caps[n].type != algorithm)
                    continue;
                VAProcFilterParameterBufferDeinterlacing param = {0};
                param.type = VAProcFilterDeinterlacing;
                param.algorithm = algorithm;
                buffers[VAProcFilterDeinterlacing] =
                    va_create_filter_buffer(vf, sizeof(param), 1, &param);
            }
            if (buffers[VAProcFilterDeinterlacing] == VA_INVALID_ID)
                MP_WARN(vf, "Selected deinterlacing algorithm not supported.\n");
        } // check other filters
    }
    if (p->opts->deint_type < 0)
        p->opts->deint_type = 0;
    p->num_buffers = 0;
    if (buffers[VAProcFilterDeinterlacing] != VA_INVALID_ID)
        p->buffers[p->num_buffers++] = buffers[VAProcFilterDeinterlacing];
    p->do_deint = !!p->opts->deint_type;
    // next filters: p->buffers[p->num_buffers++] = buffers[next_filter];
    return true;
}