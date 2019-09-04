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

/* Variables and functions */
 int /*<<< orphan*/  OSSL_NELEM (int /*<<< orphan*/ ) ; 
 char const* enum_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ssl_alerts ; 

const char *ssl_alert_name(int alert)
{
    return enum_name(ssl_alerts, OSSL_NELEM(ssl_alerts), alert);
}