#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
struct TYPE_14__ {int transformed; TYPE_1__* prsoptions; TYPE_1__* query; TYPE_2__* prsobj; TYPE_3__* cfg; TYPE_1__* prs; } ;
struct TYPE_13__ {int /*<<< orphan*/  cfgId; } ;
struct TYPE_12__ {int /*<<< orphan*/  prsheadline; } ;
struct TYPE_11__ {scalar_t__ curwords; } ;
typedef  TYPE_1__* TSQuery ;
typedef  TYPE_2__ TSParserCacheEntry ;
typedef  TYPE_3__ TSConfigCacheEntry ;
typedef  TYPE_1__ List ;
typedef  TYPE_1__ HeadlineParsedText ;
typedef  TYPE_6__ HeadlineJsonState ;

/* Variables and functions */
 int /*<<< orphan*/  FunctionCall3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (TYPE_1__*) ; 
 int /*<<< orphan*/ * generateHeadline (TYPE_1__*) ; 
 int /*<<< orphan*/  hlparsetext (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,char*,int) ; 

__attribute__((used)) static text *
headline_json_value(void *_state, char *elem_value, int elem_len)
{
	HeadlineJsonState *state = (HeadlineJsonState *) _state;

	HeadlineParsedText *prs = state->prs;
	TSConfigCacheEntry *cfg = state->cfg;
	TSParserCacheEntry *prsobj = state->prsobj;
	TSQuery		query = state->query;
	List	   *prsoptions = state->prsoptions;

	prs->curwords = 0;
	hlparsetext(cfg->cfgId, prs, query, elem_value, elem_len);
	FunctionCall3(&(prsobj->prsheadline),
				  PointerGetDatum(prs),
				  PointerGetDatum(prsoptions),
				  PointerGetDatum(query));

	state->transformed = true;
	return generateHeadline(prs);
}