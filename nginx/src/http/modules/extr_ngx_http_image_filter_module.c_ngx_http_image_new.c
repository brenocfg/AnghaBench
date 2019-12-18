#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
typedef  int /*<<< orphan*/ * gdImagePtr ;
struct TYPE_4__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/ * gdImageCreate (int,int) ; 
 int /*<<< orphan*/ * gdImageCreateTrueColor (int,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static gdImagePtr
ngx_http_image_new(ngx_http_request_t *r, int w, int h, int colors)
{
    gdImagePtr  img;

    if (colors == 0) {
        img = gdImageCreateTrueColor(w, h);

        if (img == NULL) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "gdImageCreateTrueColor() failed");
            return NULL;
        }

    } else {
        img = gdImageCreate(w, h);

        if (img == NULL) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "gdImageCreate() failed");
            return NULL;
        }
    }

    return img;
}