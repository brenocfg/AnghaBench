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
typedef  int /*<<< orphan*/  json_stream ;
typedef  int /*<<< orphan*/  errbuf ;

/* Variables and functions */
 int /*<<< orphan*/  json_error (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  strerror_r (int,char*,int) ; 

__attribute__((used)) static void json_error_s(json_stream *json, int err)
{
    char errbuf[1024] = {0};
    strerror_r(err, errbuf, sizeof(errbuf));
    json_error(json, "%s", errbuf);
}