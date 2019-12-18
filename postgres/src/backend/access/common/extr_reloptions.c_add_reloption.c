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
typedef  int /*<<< orphan*/  relopt_gen ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/ ** custom_options ; 
 int need_initialization ; 
 int num_custom_options ; 
 int /*<<< orphan*/ ** palloc (int) ; 
 int /*<<< orphan*/ ** repalloc (int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static void
add_reloption(relopt_gen *newoption)
{
	static int	max_custom_options = 0;

	if (num_custom_options >= max_custom_options)
	{
		MemoryContext oldcxt;

		oldcxt = MemoryContextSwitchTo(TopMemoryContext);

		if (max_custom_options == 0)
		{
			max_custom_options = 8;
			custom_options = palloc(max_custom_options * sizeof(relopt_gen *));
		}
		else
		{
			max_custom_options *= 2;
			custom_options = repalloc(custom_options,
									  max_custom_options * sizeof(relopt_gen *));
		}
		MemoryContextSwitchTo(oldcxt);
	}
	custom_options[num_custom_options++] = newoption;

	need_initialization = true;
}