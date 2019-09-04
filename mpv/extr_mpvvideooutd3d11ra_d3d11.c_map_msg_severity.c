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
typedef  int D3D11_MESSAGE_SEVERITY ;

/* Variables and functions */
#define  D3D11_MESSAGE_SEVERITY_CORRUPTION 132 
#define  D3D11_MESSAGE_SEVERITY_ERROR 131 
#define  D3D11_MESSAGE_SEVERITY_INFO 130 
#define  D3D11_MESSAGE_SEVERITY_MESSAGE 129 
#define  D3D11_MESSAGE_SEVERITY_WARNING 128 
 int MSGL_DEBUG ; 
 int MSGL_ERR ; 
 int MSGL_FATAL ; 
 int MSGL_WARN ; 

__attribute__((used)) static int map_msg_severity(D3D11_MESSAGE_SEVERITY sev)
{
    switch (sev) {
    case D3D11_MESSAGE_SEVERITY_CORRUPTION:
        return MSGL_FATAL;
    case D3D11_MESSAGE_SEVERITY_ERROR:
        return MSGL_ERR;
    case D3D11_MESSAGE_SEVERITY_WARNING:
        return MSGL_WARN;
    default:
    case D3D11_MESSAGE_SEVERITY_INFO:
    case D3D11_MESSAGE_SEVERITY_MESSAGE:
        return MSGL_DEBUG;
    }
}