#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int tap_sleep; int /*<<< orphan*/  ip_win32_type; } ;
struct options {scalar_t__ inetd; int ifconfig_noexec; int route_delay_defined; scalar_t__ mode; int route_delay; scalar_t__* pkcs11_providers; scalar_t__ pkcs11_id_management; scalar_t__ pkcs11_id; TYPE_1__ tuntap_options; scalar_t__ wintun; int /*<<< orphan*/  dev_type; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_PKCS11_MODULE ; 
 int const DEV_TYPE_TAP ; 
 int const DEV_TYPE_TUN ; 
 scalar_t__ INETD_NOWAIT ; 
 int /*<<< orphan*/  IPW32_SET_IPAPI ; 
 int /*<<< orphan*/  IPW32_SET_MANUAL ; 
 scalar_t__ MODE_POINT_TO_POINT ; 
 scalar_t__ MODE_SERVER ; 
 int dev_type_enum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remap_redirect_gateway_flags (struct options*) ; 

__attribute__((used)) static void
options_postprocess_mutate_invariant(struct options *options)
{
#ifdef _WIN32
    const int dev = dev_type_enum(options->dev, options->dev_type);
#endif

    /*
     * In forking TCP server mode, you don't need to ifconfig
     * the tap device (the assumption is that it will be bridged).
     */
    if (options->inetd == INETD_NOWAIT)
    {
        options->ifconfig_noexec = true;
    }

#ifdef _WIN32
    if ((dev == DEV_TYPE_TUN || dev == DEV_TYPE_TAP) && !options->route_delay_defined)
    {
        if (options->mode == MODE_POINT_TO_POINT)
        {
            options->route_delay_defined = true;
            options->route_delay = 5; /* Vista sometimes has a race without this */
        }
    }

    if (options->ifconfig_noexec)
    {
        options->tuntap_options.ip_win32_type = IPW32_SET_MANUAL;
        options->ifconfig_noexec = false;
    }

    /* for wintun kernel doesn't send DHCP requests, so use ipapi to set IP address and netmask */
    if (options->wintun)
    {
        options->tuntap_options.ip_win32_type = IPW32_SET_IPAPI;
    }

    remap_redirect_gateway_flags(options);
#endif

#if P2MP_SERVER
    /*
     * Check consistency of --mode server options.
     */
    if (options->mode == MODE_SERVER)
    {
#ifdef _WIN32
        /*
         * We need to explicitly set --tap-sleep because
         * we do not schedule event timers in the top-level context.
         */
        options->tuntap_options.tap_sleep = 10;
        if (options->route_delay_defined && options->route_delay)
        {
            options->tuntap_options.tap_sleep = options->route_delay;
        }
        options->route_delay_defined = false;
#endif
    }
#endif

#ifdef DEFAULT_PKCS11_MODULE
    /* If p11-kit is present on the system then load its p11-kit-proxy.so
     * by default if the user asks for PKCS#11 without otherwise specifying
     * the module to use. */
    if (!options->pkcs11_providers[0]
        && (options->pkcs11_id || options->pkcs11_id_management))
    {
        options->pkcs11_providers[0] = DEFAULT_PKCS11_MODULE;
    }
#endif
}