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
struct mp_log {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  d3d11_load ; 
 int /*<<< orphan*/  d3d11_once ; 
 int /*<<< orphan*/  mp_fatal (struct mp_log*,char*,char*,char*) ; 
 scalar_t__ pCreateDXGIFactory1 ; 
 scalar_t__ pD3D11CreateDevice ; 
 int /*<<< orphan*/  pthread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool load_d3d11_functions(struct mp_log *log)
{
    pthread_once(&d3d11_once, d3d11_load);
    if (!pD3D11CreateDevice || !pCreateDXGIFactory1) {
        mp_fatal(log, "Failed to load base d3d11 functionality: "
                      "CreateDevice: %s, CreateDXGIFactory1: %s\n",
                 pD3D11CreateDevice ? "success" : "failure",
                 pCreateDXGIFactory1 ? "success": "failure");
        return false;
    }

    return true;
}