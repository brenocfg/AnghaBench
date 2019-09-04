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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  YY_BUF_SIZE ; 
 int /*<<< orphan*/  YY_CURRENT_BUFFER ; 
 int /*<<< orphan*/  YY_CURRENT_BUFFER_LVALUE ; 
 int /*<<< orphan*/  hlsl__create_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlsl__init_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlsl__load_buffer_state () ; 
 int /*<<< orphan*/  hlsl_ensure_buffer_stack () ; 
 int /*<<< orphan*/  hlsl_in ; 

void hlsl_restart  (FILE * input_file )
{
    
	if ( ! YY_CURRENT_BUFFER ){
        hlsl_ensure_buffer_stack ();
		YY_CURRENT_BUFFER_LVALUE =
            hlsl__create_buffer(hlsl_in,YY_BUF_SIZE );
	}

	hlsl__init_buffer(YY_CURRENT_BUFFER,input_file );
	hlsl__load_buffer_state( );
}