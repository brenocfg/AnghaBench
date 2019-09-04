#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int time_t ;
typedef  int ngx_uint_t ;
struct TYPE_4__ {int len; char* data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
typedef  scalar_t__ ngx_http_expires_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_EXPIRES_DAILY ; 
 scalar_t__ NGX_HTTP_EXPIRES_EPOCH ; 
 scalar_t__ NGX_HTTP_EXPIRES_MAX ; 
 scalar_t__ NGX_HTTP_EXPIRES_MODIFIED ; 
 scalar_t__ NGX_HTTP_EXPIRES_OFF ; 
 scalar_t__ NGX_OK ; 
 int ngx_parse_time (TYPE_1__*,int) ; 
 scalar_t__ ngx_strncmp (char*,char*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_parse_expires(ngx_str_t *value, ngx_http_expires_t *expires,
    time_t *expires_time, char **err)
{
    ngx_uint_t  minus;

    if (*expires != NGX_HTTP_EXPIRES_MODIFIED) {

        if (value->len == 5 && ngx_strncmp(value->data, "epoch", 5) == 0) {
            *expires = NGX_HTTP_EXPIRES_EPOCH;
            return NGX_OK;
        }

        if (value->len == 3 && ngx_strncmp(value->data, "max", 3) == 0) {
            *expires = NGX_HTTP_EXPIRES_MAX;
            return NGX_OK;
        }

        if (value->len == 3 && ngx_strncmp(value->data, "off", 3) == 0) {
            *expires = NGX_HTTP_EXPIRES_OFF;
            return NGX_OK;
        }
    }

    if (value->len && value->data[0] == '@') {
        value->data++;
        value->len--;
        minus = 0;

        if (*expires == NGX_HTTP_EXPIRES_MODIFIED) {
            *err = "daily time cannot be used with \"modified\" parameter";
            return NGX_ERROR;
        }

        *expires = NGX_HTTP_EXPIRES_DAILY;

    } else if (value->len && value->data[0] == '+') {
        value->data++;
        value->len--;
        minus = 0;

    } else if (value->len && value->data[0] == '-') {
        value->data++;
        value->len--;
        minus = 1;

    } else {
        minus = 0;
    }

    *expires_time = ngx_parse_time(value, 1);

    if (*expires_time == (time_t) NGX_ERROR) {
        *err = "invalid value";
        return NGX_ERROR;
    }

    if (*expires == NGX_HTTP_EXPIRES_DAILY
        && *expires_time > 24 * 60 * 60)
    {
        *err = "daily time value must be less than 24 hours";
        return NGX_ERROR;
    }

    if (minus) {
        *expires_time = - *expires_time;
    }

    return NGX_OK;
}