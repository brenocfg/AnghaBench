#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_6__ {scalar_t__ curwords; int /*<<< orphan*/ * words; } ;
struct TYPE_5__ {int /*<<< orphan*/  cfgId; TYPE_2__* prs; } ;
typedef  TYPE_1__ TSVectorBuildState ;
typedef  int /*<<< orphan*/  TSVector ;
typedef  TYPE_2__ ParsedText ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Jsonb ;

/* Variables and functions */
 int /*<<< orphan*/  add_to_tsvector ; 
 int /*<<< orphan*/  iterate_jsonb_values (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_tsvector (TYPE_2__*) ; 

__attribute__((used)) static TSVector
jsonb_to_tsvector_worker(Oid cfgId, Jsonb *jb, uint32 flags)
{
	TSVectorBuildState state;
	ParsedText	prs;

	prs.words = NULL;
	prs.curwords = 0;
	state.prs = &prs;
	state.cfgId = cfgId;

	iterate_jsonb_values(jb, flags, &state, add_to_tsvector);

	return make_tsvector(&prs);
}