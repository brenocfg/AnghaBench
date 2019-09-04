#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t chanlist; TYPE_5__* tv_channel_current; int /*<<< orphan*/  norm; struct CHANLIST* chanlist_s; TYPE_5__* tv_channel_list; TYPE_1__* tv_param; } ;
typedef  TYPE_2__ tvi_handle_t ;
typedef  int /*<<< orphan*/  tv_channels_t ;
struct CHANLIST {int freq; int /*<<< orphan*/  name; } ;
struct TYPE_12__ {int count; } ;
struct TYPE_11__ {int index; char* name; char* number; int freq; struct TYPE_11__* next; struct TYPE_11__* prev; int /*<<< orphan*/  norm; } ;
struct TYPE_9__ {char** channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (TYPE_2__*,char*,char*,char*) ; 
 int /*<<< orphan*/  MP_INFO (TYPE_2__*,char*) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  av_strlcpy (char*,char*,int) ; 
 TYPE_6__* chanlists ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  norm_from_string (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static void parse_channels(tvi_handle_t *tvh)
{
    char** channels = tvh->tv_param->channels;

    MP_INFO(tvh, "TV channel names detected.\n");
    tvh->tv_channel_list = malloc(sizeof(tv_channels_t));
    tvh->tv_channel_list->index=1;
    tvh->tv_channel_list->next=NULL;
    tvh->tv_channel_list->prev=NULL;
    tvh->tv_channel_current = tvh->tv_channel_list;
    tvh->tv_channel_current->norm = tvh->norm;

    while (*channels) {
        char* tmp = *(channels++);
        char* sep = strchr(tmp,'-');
        int i;
        struct CHANLIST cl;

        if (!sep) continue; // Wrong syntax, but mplayer should not crash

        av_strlcpy(tvh->tv_channel_current->name, sep + 1,
                        sizeof(tvh->tv_channel_current->name));
        sep[0] = '\0';
        strncpy(tvh->tv_channel_current->number, tmp, 5);
        tvh->tv_channel_current->number[4]='\0';

        while ((sep=strchr(tvh->tv_channel_current->name, '_')))
            sep[0] = ' ';

        // if channel number is a number and larger than 1000 threat it as frequency
        // tmp still contain pointer to null-terminated string with channel number here
        if (atoi(tmp)>1000){
            tvh->tv_channel_current->freq=atoi(tmp);
        }else{
            tvh->tv_channel_current->freq = 0;
            for (i = 0; i < chanlists[tvh->chanlist].count; i++) {
                cl = tvh->chanlist_s[i];
                if (!strcasecmp(cl.name, tvh->tv_channel_current->number)) {
                    tvh->tv_channel_current->freq=cl.freq;
                    break;
                }
            }
        }
        if (tvh->tv_channel_current->freq == 0)
            MP_ERR(tvh, "Couldn't find frequency for channel %s (%s)\n",
                            tvh->tv_channel_current->number, tvh->tv_channel_current->name);
        else {
          sep = strchr(tvh->tv_channel_current->name, '-');
          if ( !sep ) sep = strchr(tvh->tv_channel_current->name, '+');

          if ( sep ) {
            i = atoi (sep+1);
            if ( sep[0] == '+' ) tvh->tv_channel_current->freq += i * 100;
            if ( sep[0] == '-' ) tvh->tv_channel_current->freq -= i * 100;
            sep[0] = '\0';
          }

          sep = strchr(tvh->tv_channel_current->name, '=');
          if ( sep ) {
            tvh->tv_channel_current->norm = norm_from_string(tvh, sep+1);
            sep[0] = '\0';
          }
        }

        /*MP_INFO(tvh, "-- Detected channel %s - %s (%5.3f)\n",
                        tvh->tv_channel_current->number, tvh->tv_channel_current->name,
                        (float)tvh->tv_channel_current->freq/1000);*/

        tvh->tv_channel_current->next = malloc(sizeof(tv_channels_t));
        tvh->tv_channel_current->next->index = tvh->tv_channel_current->index + 1;
        tvh->tv_channel_current->next->prev = tvh->tv_channel_current;
        tvh->tv_channel_current->next->next = NULL;
        tvh->tv_channel_current = tvh->tv_channel_current->next;
        tvh->tv_channel_current->norm = tvh->norm;
    }
    if (tvh->tv_channel_current->prev)
        tvh->tv_channel_current->prev->next = NULL;
    free(tvh->tv_channel_current);
}