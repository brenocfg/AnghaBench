#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ depth; scalar_t__ max_depth; } ;
typedef  TYPE_1__ xmlreader ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  SC_E_MAXELEMENTDEPTH ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT reader_inc_depth(xmlreader *reader)
{
    return (++reader->depth >= reader->max_depth && reader->max_depth) ? SC_E_MAXELEMENTDEPTH : S_OK;
}