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
struct platform_device {int dummy; } ;
struct iss_device {int /*<<< orphan*/  crashed; } ;

/* Variables and functions */
 int /*<<< orphan*/  iss_cleanup_modules (struct iss_device*) ; 
 int /*<<< orphan*/  iss_unregister_entities (struct iss_device*) ; 
 int /*<<< orphan*/  media_entity_enum_cleanup (int /*<<< orphan*/ *) ; 
 struct iss_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int iss_remove(struct platform_device *pdev)
{
	struct iss_device *iss = platform_get_drvdata(pdev);

	iss_unregister_entities(iss);
	media_entity_enum_cleanup(&iss->crashed);
	iss_cleanup_modules(iss);

	return 0;
}