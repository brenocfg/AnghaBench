#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_12__ ;

/* Type definitions */
struct TYPE_19__ {int chanlist; int channel; struct CHANLIST* chanlist_s; int /*<<< orphan*/  tv_channel_last_real; TYPE_1__* tv_param; int /*<<< orphan*/  priv; TYPE_9__* tv_channel_current; TYPE_9__* tv_channel_last; TYPE_9__* tv_channel_list; TYPE_3__* functions; } ;
typedef  TYPE_2__ tvi_handle_t ;
struct TYPE_20__ {scalar_t__ (* control ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
typedef  TYPE_3__ tvi_functions_t ;
typedef  int /*<<< orphan*/  tv_fmt_list ;
struct CHANLIST {double freq; int /*<<< orphan*/ * name; } ;
struct TYPE_21__ {struct TYPE_21__* next; int /*<<< orphan*/  name; } ;
struct TYPE_18__ {int outfmt; int input; scalar_t__ normid; int width; int height; long freq; int /*<<< orphan*/ * channel; scalar_t__ channels; int /*<<< orphan*/ * chanlist; int /*<<< orphan*/  norm; int /*<<< orphan*/  driver; } ;
struct TYPE_17__ {int count; int /*<<< orphan*/ * name; struct CHANLIST* list; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (TYPE_2__*,char*,...) ; 
#define  MP_FOURCC_BGR15 139 
#define  MP_FOURCC_BGR16 138 
#define  MP_FOURCC_BGR24 137 
#define  MP_FOURCC_BGR32 136 
#define  MP_FOURCC_I420 135 
#define  MP_FOURCC_RGB15 134 
#define  MP_FOURCC_RGB16 133 
#define  MP_FOURCC_RGB24 132 
#define  MP_FOURCC_RGB32 131 
#define  MP_FOURCC_UYVY 130 
#define  MP_FOURCC_YUY2 129 
#define  MP_FOURCC_YV12 128 
 int /*<<< orphan*/  MP_INFO (TYPE_2__*,char*,int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_2__*,char*,unsigned long,...) ; 
 int /*<<< orphan*/  MP_WARN (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  TVI_CONTROL_IS_TUNER ; 
 int /*<<< orphan*/  TVI_CONTROL_IS_VIDEO ; 
 int /*<<< orphan*/  TVI_CONTROL_SPC_SET_INPUT ; 
 scalar_t__ TVI_CONTROL_TRUE ; 
 int /*<<< orphan*/  TVI_CONTROL_TUN_GET_FREQ ; 
 int /*<<< orphan*/  TVI_CONTROL_TUN_SET_FREQ ; 
 int /*<<< orphan*/  TVI_CONTROL_VID_CHK_HEIGHT ; 
 int /*<<< orphan*/  TVI_CONTROL_VID_CHK_WIDTH ; 
 int /*<<< orphan*/  TVI_CONTROL_VID_GET_HEIGHT ; 
 int /*<<< orphan*/  TVI_CONTROL_VID_GET_WIDTH ; 
 int /*<<< orphan*/  TVI_CONTROL_VID_SET_FORMAT ; 
 int /*<<< orphan*/  TVI_CONTROL_VID_SET_HEIGHT ; 
 int /*<<< orphan*/  TVI_CONTROL_VID_SET_WIDTH ; 
 int /*<<< orphan*/  TVI_CONTROL_VID_SET_WIDTH_HEIGHT ; 
 int atoi (int /*<<< orphan*/ *) ; 
 TYPE_12__* chanlists ; 
 int /*<<< orphan*/  malloc (int) ; 
 scalar_t__ mp_isdigit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_channels (TYPE_2__*) ; 
 int /*<<< orphan*/  set_norm_and_freq (TYPE_2__*,TYPE_9__*) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub11 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub12 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub13 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 
 scalar_t__ stub14 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub9 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  tv_get_freq (TYPE_2__*,unsigned long*) ; 
 int /*<<< orphan*/  tv_set_freq_float (TYPE_2__*,double) ; 
 int /*<<< orphan*/  tv_set_norm (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tv_set_norm_i (TYPE_2__*,scalar_t__) ; 

int open_tv(tvi_handle_t *tvh)
{
    int i;
    const tvi_functions_t *funcs = tvh->functions;
    static const int tv_fmt_list[] = {
      MP_FOURCC_YV12,
      MP_FOURCC_I420,
      MP_FOURCC_UYVY,
      MP_FOURCC_YUY2,
      MP_FOURCC_RGB32,
      MP_FOURCC_RGB24,
      MP_FOURCC_RGB16,
      MP_FOURCC_RGB15
    };

    if (funcs->control(tvh->priv, TVI_CONTROL_IS_VIDEO, 0) != TVI_CONTROL_TRUE)
    {
        MP_ERR(tvh, "Error: No video input present!\n");
        return 0;
    }

    if (tvh->tv_param->outfmt == -1)
      for (i = 0; i < sizeof (tv_fmt_list) / sizeof (*tv_fmt_list); i++)
        {
          tvh->tv_param->outfmt = tv_fmt_list[i];
          if (funcs->control (tvh->priv, TVI_CONTROL_VID_SET_FORMAT,
                              &tvh->tv_param->outfmt) == TVI_CONTROL_TRUE)
            break;
        }
    else
    {
    switch(tvh->tv_param->outfmt)
    {
        case MP_FOURCC_YV12:
        case MP_FOURCC_I420:
        case MP_FOURCC_UYVY:
        case MP_FOURCC_YUY2:
        case MP_FOURCC_RGB32:
        case MP_FOURCC_RGB24:
        case MP_FOURCC_BGR32:
        case MP_FOURCC_BGR24:
        case MP_FOURCC_BGR16:
        case MP_FOURCC_BGR15:
            break;
        default:
            MP_ERR(tvh, "==================================================================\n"\
                        " WARNING: UNTESTED OR UNKNOWN OUTPUT IMAGE FORMAT REQUESTED (0x%x)\n"\
                        " This may cause buggy playback or program crash! Bug reports will\n"\
                        " be ignored! You should try again with YV12 (which is the default\n"\
                        " colorspace) and read the documentation!\n"\
                        "==================================================================\n"
                ,tvh->tv_param->outfmt);
    }
    funcs->control(tvh->priv, TVI_CONTROL_VID_SET_FORMAT, &tvh->tv_param->outfmt);
    }

    /* set some params got from cmdline */
    funcs->control(tvh->priv, TVI_CONTROL_SPC_SET_INPUT, &tvh->tv_param->input);

    if ((!strcmp(tvh->tv_param->driver, "v4l2") && tvh->tv_param->normid >= 0))
        tv_set_norm_i(tvh, tvh->tv_param->normid);
    else
        tv_set_norm(tvh,tvh->tv_param->norm);

    /* limits on w&h are norm-dependent -- JM */
    if (tvh->tv_param->width != -1 && tvh->tv_param->height != -1) {
        // first tell the driver both width and height, some drivers do not support setting them independently.
        int dim[2];
        dim[0] = tvh->tv_param->width; dim[1] = tvh->tv_param->height;
        funcs->control(tvh->priv, TVI_CONTROL_VID_SET_WIDTH_HEIGHT, dim);
    }
    /* set width */
    if (tvh->tv_param->width != -1)
    {
        if (funcs->control(tvh->priv, TVI_CONTROL_VID_CHK_WIDTH, &tvh->tv_param->width) == TVI_CONTROL_TRUE)
            funcs->control(tvh->priv, TVI_CONTROL_VID_SET_WIDTH, &tvh->tv_param->width);
        else
        {
            MP_ERR(tvh, "Unable to set requested width: %d\n", tvh->tv_param->width);
            funcs->control(tvh->priv, TVI_CONTROL_VID_GET_WIDTH, &tvh->tv_param->width);
        }
    }

    /* set height */
    if (tvh->tv_param->height != -1)
    {
        if (funcs->control(tvh->priv, TVI_CONTROL_VID_CHK_HEIGHT, &tvh->tv_param->height) == TVI_CONTROL_TRUE)
            funcs->control(tvh->priv, TVI_CONTROL_VID_SET_HEIGHT, &tvh->tv_param->height);
        else
        {
            MP_ERR(tvh, "Unable to set requested height: %d\n", tvh->tv_param->height);
            funcs->control(tvh->priv, TVI_CONTROL_VID_GET_HEIGHT, &tvh->tv_param->height);
        }
    }

    if (funcs->control(tvh->priv, TVI_CONTROL_IS_TUNER, 0) != TVI_CONTROL_TRUE)
    {
        MP_WARN(tvh, "Selected input hasn't got a tuner!\n");
        goto done;
    }

    /* select channel list */
    for (i = 0; chanlists[i].name != NULL; i++)
    {
        if (!strcasecmp(chanlists[i].name, tvh->tv_param->chanlist))
        {
            tvh->chanlist = i;
            tvh->chanlist_s = chanlists[i].list;
            break;
        }
    }

    if (tvh->chanlist == -1) {
        MP_WARN(tvh, "Unable to find selected channel list! (%s)\n",
            tvh->tv_param->chanlist);
        return 0;
    } else
        MP_VERBOSE(tvh, "Selected channel list: %s (including %d channels)\n",
            chanlists[tvh->chanlist].name, chanlists[tvh->chanlist].count);

    if (tvh->tv_param->freq && tvh->tv_param->channel)
    {
        MP_WARN(tvh, "You can't set frequency and channel simultaneously!\n");
        goto done;
    }

    /* Handle channel names */
    if (tvh->tv_param->channels) {
        parse_channels(tvh);
    } else
            tvh->tv_channel_last_real = malloc(5);

    if (tvh->tv_channel_list) {
        int channel = 0;
        if (tvh->tv_param->channel)
         {
           if (mp_isdigit(*tvh->tv_param->channel))
                /* if tvh->tv_param->channel begins with a digit interpret it as a number */
                channel = atoi(tvh->tv_param->channel);
           else
              {
                /* if tvh->tv_param->channel does not begin with a digit
                   set the first channel that contains tvh->tv_param->channel in its name */

                tvh->tv_channel_current = tvh->tv_channel_list;
                while ( tvh->tv_channel_current ) {
                        if ( strstr(tvh->tv_channel_current->name, tvh->tv_param->channel) )
                          break;
                        tvh->tv_channel_current = tvh->tv_channel_current->next;
                        }
                if ( !tvh->tv_channel_current ) tvh->tv_channel_current = tvh->tv_channel_list;
              }
         }
        else
                channel = 1;

        if ( channel ) {
        tvh->tv_channel_current = tvh->tv_channel_list;
        for (int n = 1; n < channel; n++)
                if (tvh->tv_channel_current->next)
                        tvh->tv_channel_current = tvh->tv_channel_current->next;
        }

        set_norm_and_freq(tvh, tvh->tv_channel_current);
        tvh->tv_channel_last = tvh->tv_channel_current;
    } else {
    /* we need to set frequency */
    if (tvh->tv_param->freq)
    {
        unsigned long freq = tvh->tv_param->freq * 16;

        /* set freq in MHz */
        funcs->control(tvh->priv, TVI_CONTROL_TUN_SET_FREQ, &freq);

        funcs->control(tvh->priv, TVI_CONTROL_TUN_GET_FREQ, &freq);
        MP_VERBOSE(tvh, "Selected frequency: %lu (%.3f)\n",
            freq, freq/16.0);
    }

            if (tvh->tv_param->channel) {
        struct CHANLIST cl;

        MP_VERBOSE(tvh, "Requested channel: %s\n", tvh->tv_param->channel);
        for (i = 0; i < chanlists[tvh->chanlist].count; i++)
        {
            cl = tvh->chanlist_s[i];
                    //  printf("count%d: name: %s, freq: %d\n",
                    //  i, cl.name, cl.freq);
            if (!strcasecmp(cl.name, tvh->tv_param->channel))
            {
                        strcpy(tvh->tv_channel_last_real, cl.name);
                tvh->channel = i;
                MP_INFO(tvh, "Selected channel: %s (freq: %.3f)\n",
                    cl.name, cl.freq/1000.0);
                tv_set_freq_float(tvh, cl.freq);
                break;
            }
        }
    }
    }

    /* grep frequency in chanlist */
    {
        unsigned long i2 = 0;
        int freq;

        tv_get_freq(tvh, &i2);

        freq = (int) (((float)(i2/16))*1000)+250;

        for (i = 0; i < chanlists[tvh->chanlist].count; i++)
        {
            if (tvh->chanlist_s[i].freq == freq)
            {
                tvh->channel = i+1;
                break;
            }
        }
    }

done:
    /* also start device! */
        return 1;
}