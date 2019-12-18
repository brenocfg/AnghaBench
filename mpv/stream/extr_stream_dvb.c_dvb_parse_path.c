#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/  path; TYPE_7__* priv; } ;
typedef  TYPE_5__ stream_t ;
struct TYPE_25__ {int cur_adapter; int adapters_count; TYPE_4__* adapters; } ;
typedef  TYPE_6__ dvb_state_t ;
struct TYPE_26__ {scalar_t__ devno; void* prog; TYPE_1__* opts; TYPE_6__* state; } ;
typedef  TYPE_7__ dvb_priv_t ;
struct TYPE_27__ {scalar_t__ len; } ;
typedef  TYPE_8__ bstr ;
struct TYPE_23__ {scalar_t__ devno; TYPE_3__* list; } ;
struct TYPE_22__ {TYPE_2__* channels; } ;
struct TYPE_21__ {int /*<<< orphan*/ * name; } ;
struct TYPE_20__ {scalar_t__ cfg_devno; int /*<<< orphan*/ * cfg_prog; } ;

/* Variables and functions */
 scalar_t__ BSTR_P (TYPE_8__) ; 
 scalar_t__ MAX_ADAPTERS ; 
 int /*<<< orphan*/  MP_ERR (TYPE_5__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_5__*,char*,void*,scalar_t__) ; 
 int /*<<< orphan*/  bstr0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstr_split_tok (int /*<<< orphan*/ ,char*,TYPE_8__*,TYPE_8__*) ; 
 void* bstrto0 (TYPE_7__*,TYPE_8__) ; 
 scalar_t__ bstrtoll (TYPE_8__,TYPE_8__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (void*) ; 
 void* talloc_strdup (TYPE_7__*,int /*<<< orphan*/ *) ; 

int dvb_parse_path(stream_t *stream)
{
    dvb_priv_t *priv = stream->priv;
    dvb_state_t *state = priv->state;

    // Parse stream path. Common rule: cfg wins over stream path,
    // since cfg may be changed at runtime.
    bstr prog, devno;
    if (!bstr_split_tok(bstr0(stream->path), "@", &devno, &prog)) {
        prog = devno;
        devno.len = 0;
    }

    if (priv->opts->cfg_devno != 0) {
        priv->devno = priv->opts->cfg_devno;
    } else if (devno.len) {
        bstr r;
        priv->devno = bstrtoll(devno, &r, 0);
        if (r.len || priv->devno < 0 || priv->devno >= MAX_ADAPTERS) {
            MP_ERR(stream, "invalid devno: '%.*s'\n", BSTR_P(devno));
            return 0;
        }
    } else {
        // Default to the default of cfg_devno.
        priv->devno = priv->opts->cfg_devno;
    }

    // Current adapter is derived from devno.
    state->cur_adapter = -1;
    for (int i = 0; i < state->adapters_count; i++) {
        if (state->adapters[i].devno == priv->devno) {
            state->cur_adapter = i;
            break;
        }
    }

    if (state->cur_adapter == -1) {
        MP_ERR(stream, "NO CONFIGURATION FOUND FOR ADAPTER N. %d!\n",
               priv->devno);
        return 0;
    }

    if (priv->opts->cfg_prog != NULL && strlen(priv->opts->cfg_prog) > 0) {
        talloc_free(priv->prog);
        priv->prog = talloc_strdup(priv, priv->opts->cfg_prog);
    } else if (prog.len) {
        talloc_free(priv->prog);
        priv->prog = bstrto0(priv, prog);
    } else {
        // We use the first program from the channel list.
        if (state->adapters[state->cur_adapter].list == NULL) {
            MP_ERR(stream, "No channel list available for adapter %d!\n", priv->devno);
            return 0;
        }
        talloc_free(priv->prog);
        priv->prog = talloc_strdup(priv, state->adapters[state->cur_adapter].list->channels[0].name);
    }

    MP_VERBOSE(stream, "DVB_CONFIG: prog=%s, devno=%d\n",
               priv->prog, priv->devno);
    return 1;
}