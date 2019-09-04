#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct web_client {int dummy; } ;
typedef  int /*<<< orphan*/  RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/  health_api_v1_chart_variables2json ; 
 int web_client_api_request_single_chart (int /*<<< orphan*/ *,struct web_client*,char*,int /*<<< orphan*/ ) ; 

inline int web_client_api_request_v1_alarm_variables(RRDHOST *host, struct web_client *w, char *url) {
    return web_client_api_request_single_chart(host, w, url, health_api_v1_chart_variables2json);
}