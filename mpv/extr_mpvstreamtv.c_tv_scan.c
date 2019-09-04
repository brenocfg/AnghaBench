#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
struct TYPE_18__ {size_t chanlist; struct CHANLIST* chanlist_s; TYPE_4__* scan; TYPE_5__* tv_channel_current; TYPE_5__* tv_channel_list; TYPE_2__* tv_param; int /*<<< orphan*/  priv; TYPE_1__* functions; } ;
typedef  TYPE_3__ tvi_handle_t ;
struct TYPE_19__ {size_t channel_num; unsigned int scan_timer; int /*<<< orphan*/  new_channels; } ;
typedef  TYPE_4__ tv_scan_t ;
struct TYPE_20__ {int freq; int index; int name; char* number; struct TYPE_20__* next; struct TYPE_20__* prev; } ;
typedef  TYPE_5__ tv_channels_t ;
struct CHANLIST {int freq; char* name; } ;
struct TYPE_17__ {int scan_period; scalar_t__ scan_threshold; scalar_t__ scan; } ;
struct TYPE_16__ {scalar_t__ (* control ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_15__ {size_t count; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_INFO (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  MP_WARN (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  TVI_CONTROL_IS_TUNER ; 
 scalar_t__ TVI_CONTROL_TRUE ; 
 TYPE_4__* calloc (int,int) ; 
 TYPE_11__* chanlists ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 TYPE_5__* malloc (int) ; 
 scalar_t__ mp_time_us () ; 
 int /*<<< orphan*/  snprintf (int,int,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tv_get_signal (TYPE_3__*) ; 
 int /*<<< orphan*/  tv_set_freq_float (TYPE_3__*,int) ; 

void tv_scan(tvi_handle_t *tvh)
{
    unsigned int now;
    struct CHANLIST cl;
    tv_channels_t *tv_channel_tmp=NULL;
    tv_channels_t *tv_channel_add=NULL;
    tv_scan_t* scan;
    int found=0, index=1;

    //Channel scanner without tuner is useless and causes crash due to uninitialized chanlist_s
    if (tvh->functions->control(tvh->priv, TVI_CONTROL_IS_TUNER, 0) != TVI_CONTROL_TRUE)
    {
        MP_WARN(tvh, "Channel scanner is not available without tuner\n");
        tvh->tv_param->scan=0;
        return;
    }

    scan = tvh->scan;
    now=(unsigned int)mp_time_us();
    if (!scan) {
        scan=calloc(1,sizeof(tv_scan_t));
        tvh->scan=scan;
        cl = tvh->chanlist_s[scan->channel_num];
        tv_set_freq_float(tvh, cl.freq);
        scan->scan_timer=now+1e6*tvh->tv_param->scan_period;
    }
    if(scan->scan_timer>now)
        return;

    if (tv_get_signal(tvh)>tvh->tv_param->scan_threshold) {
        cl = tvh->chanlist_s[scan->channel_num];
        tv_channel_tmp=tvh->tv_channel_list;
        while (tv_channel_tmp) {
            index++;
            if (cl.freq==tv_channel_tmp->freq){
                found=1;
                break;
            }
            tv_channel_add=tv_channel_tmp;
            tv_channel_tmp=tv_channel_tmp->next;
        }
        if (!found) {
            MP_INFO(tvh, "Found new channel: %s (#%d). \n",cl.name,index);
            scan->new_channels++;
            tv_channel_tmp = malloc(sizeof(tv_channels_t));
            tv_channel_tmp->index=index;
            tv_channel_tmp->next=NULL;
            tv_channel_tmp->prev=tv_channel_add;
            tv_channel_tmp->freq=cl.freq;
            snprintf(tv_channel_tmp->name,sizeof(tv_channel_tmp->name),"ch%d",index);
            strncpy(tv_channel_tmp->number, cl.name, 5);
            tv_channel_tmp->number[4]='\0';
            if (!tvh->tv_channel_list)
                tvh->tv_channel_list=tv_channel_tmp;
            else {
                tv_channel_add->next=tv_channel_tmp;
                tvh->tv_channel_list->prev=tv_channel_tmp;
            }
        }else
            MP_INFO(tvh, "Found existing channel: %s-%s.\n",
                tv_channel_tmp->number,tv_channel_tmp->name);
    }
    scan->channel_num++;
    scan->scan_timer=now+1e6*tvh->tv_param->scan_period;
    if (scan->channel_num>=chanlists[tvh->chanlist].count) {
        tvh->tv_param->scan=0;
        MP_INFO(tvh, "TV scan end. Found %d new channels.\n", scan->new_channels);
        tv_channel_tmp=tvh->tv_channel_list;
        if(tv_channel_tmp){
            MP_INFO(tvh, "channels=");
            while(tv_channel_tmp){
                MP_INFO(tvh, "%s-%s",tv_channel_tmp->number,tv_channel_tmp->name);
                if(tv_channel_tmp->next)
                    MP_INFO(tvh, ",");
                tv_channel_tmp=tv_channel_tmp->next;
            }
            MP_INFO(tvh, "\n");
        }
        if (!tvh->tv_channel_current) tvh->tv_channel_current=tvh->tv_channel_list;
        if (tvh->tv_channel_current)
            tv_set_freq_float(tvh, tvh->tv_channel_current->freq);
        free(tvh->scan);
        tvh->scan=NULL;
    }else{
        cl = tvh->chanlist_s[scan->channel_num];
        tv_set_freq_float(tvh, cl.freq);
        MP_INFO(tvh, "Trying: %s (%.2f). \n",cl.name,1e-3*cl.freq);
    }
}