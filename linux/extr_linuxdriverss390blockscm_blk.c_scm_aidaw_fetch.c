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
struct scm_request {struct aidaw* next_aidaw; } ;
struct aidaw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  memset (struct aidaw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aidaw* scm_aidaw_alloc () ; 
 unsigned int scm_aidaw_bytes (struct aidaw*) ; 

struct aidaw *scm_aidaw_fetch(struct scm_request *scmrq, unsigned int bytes)
{
	struct aidaw *aidaw;

	if (scm_aidaw_bytes(scmrq->next_aidaw) >= bytes)
		return scmrq->next_aidaw;

	aidaw = scm_aidaw_alloc();
	if (aidaw)
		memset(aidaw, 0, PAGE_SIZE);
	return aidaw;
}