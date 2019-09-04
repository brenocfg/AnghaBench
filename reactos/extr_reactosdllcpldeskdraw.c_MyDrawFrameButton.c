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
typedef  int UINT ;
typedef  int /*<<< orphan*/  LPRECT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  COLOR_SCHEME ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int BF_RECT ; 
 int BF_SOFT ; 
 int DFCS_CHECKED ; 
 int DFCS_FLAT ; 
 int DFCS_PUSHED ; 
 int EDGE_RAISED ; 
 int EDGE_SUNKEN ; 
 int /*<<< orphan*/  MyIntDrawRectEdge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL
MyDrawFrameButton(HDC hdc, LPRECT rc, UINT uState, COLOR_SCHEME *scheme)
{
    UINT edge;
    if (uState & (DFCS_PUSHED | DFCS_CHECKED | DFCS_FLAT))
        edge = EDGE_SUNKEN;
    else
        edge = EDGE_RAISED;
    return MyIntDrawRectEdge(hdc, rc, edge, (uState & DFCS_FLAT) | BF_RECT | BF_SOFT, scheme);
}