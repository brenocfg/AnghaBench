#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* tv_param; } ;
typedef  TYPE_1__ tvi_handle_t ;
struct TYPE_10__ {char* driver; } ;
typedef  TYPE_2__ tv_param_t ;
struct mp_log {int dummy; } ;
struct TYPE_11__ {char* short_name; int /*<<< orphan*/  name; TYPE_1__* (* tvi_init ) (struct mp_log*,TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MP_INFO (TYPE_1__*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_err (struct mp_log*,char*,...) ; 
 int /*<<< orphan*/  mp_info (struct mp_log*,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 TYPE_1__* stub1 (struct mp_log*,TYPE_2__*) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 
 char* talloc_strdup (int /*<<< orphan*/ *,char*) ; 
 TYPE_3__** tvi_driver_list ; 

tvi_handle_t *tv_begin(tv_param_t* tv_param, struct mp_log *log)
{
    int i;
    tvi_handle_t* h;
    if(tv_param->driver && !strcmp(tv_param->driver,"help")){
        mp_info(log, "Available drivers:\n");
        for(i=0;tvi_driver_list[i];i++){
            mp_info(log, " %s\t%s\n",tvi_driver_list[i]->short_name,tvi_driver_list[i]->name);
        }
        return NULL;
    }

    for(i=0;tvi_driver_list[i];i++){
        if (!tv_param->driver || !strcmp(tvi_driver_list[i]->short_name, tv_param->driver)){
            h=tvi_driver_list[i]->tvi_init(log, tv_param);
            //Requested driver initialization failed
            if (!h && tv_param->driver)
                return NULL;
            //Driver initialization failed during autodetection process.
            if (!h)
                continue;

            h->tv_param=tv_param;
            MP_INFO(h, "Selected driver: %s\n name: %s\n", tvi_driver_list[i]->short_name,
            tvi_driver_list[i]->name);
            talloc_free(tv_param->driver);
            tv_param->driver=talloc_strdup(NULL, tvi_driver_list[i]->short_name);
            return h;
        }
    }

    if(tv_param->driver)
        mp_err(log, "No such driver: %s\n", tv_param->driver);
    else
        mp_err(log, "TV driver autodetection failed.\n");
    return NULL;
}