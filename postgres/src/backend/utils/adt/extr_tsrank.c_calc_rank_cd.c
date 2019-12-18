#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ float4 ;
struct TYPE_22__ {int q; int p; TYPE_3__* begin; TYPE_3__* end; } ;
struct TYPE_21__ {TYPE_3__* operandData; TYPE_2__* query; } ;
struct TYPE_20__ {int /*<<< orphan*/  pos; } ;
struct TYPE_19__ {int size; } ;
struct TYPE_18__ {scalar_t__ size; } ;
typedef  TYPE_1__* TSVector ;
typedef  TYPE_2__* TSQuery ;
typedef  TYPE_3__ QueryRepresentationOperand ;
typedef  TYPE_4__ QueryRepresentation ;
typedef  TYPE_3__ DocRepresentation ;
typedef  TYPE_6__ CoverExt ;

/* Variables and functions */
 scalar_t__ Cover (TYPE_3__*,int,TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemSet (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int RANK_NORM_EXTDIST ; 
 int RANK_NORM_LENGTH ; 
 int RANK_NORM_LOGLENGTH ; 
 int RANK_NORM_LOGUNIQ ; 
 int RANK_NORM_RDIVRPLUS1 ; 
 int RANK_NORM_UNIQ ; 
 size_t WEP_GETWEIGHT (int /*<<< orphan*/ ) ; 
 int cnt_length (TYPE_1__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 TYPE_3__* get_docrep (TYPE_1__*,TYPE_4__*,int*) ; 
 int lengthof (scalar_t__ const*) ; 
 double log (double) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  pfree (TYPE_3__*) ; 
 scalar_t__ const* weights ; 

__attribute__((used)) static float4
calc_rank_cd(const float4 *arrdata, TSVector txt, TSQuery query, int method)
{
	DocRepresentation *doc;
	int			len,
				i,
				doclen = 0;
	CoverExt	ext;
	double		Wdoc = 0.0;
	double		invws[lengthof(weights)];
	double		SumDist = 0.0,
				PrevExtPos = 0.0,
				CurExtPos = 0.0;
	int			NExtent = 0;
	QueryRepresentation qr;


	for (i = 0; i < lengthof(weights); i++)
	{
		invws[i] = ((double) ((arrdata[i] >= 0) ? arrdata[i] : weights[i]));
		if (invws[i] > 1.0)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("weight out of range")));
		invws[i] = 1.0 / invws[i];
	}

	qr.query = query;
	qr.operandData = (QueryRepresentationOperand *)
		palloc0(sizeof(QueryRepresentationOperand) * query->size);

	doc = get_docrep(txt, &qr, &doclen);
	if (!doc)
	{
		pfree(qr.operandData);
		return 0.0;
	}

	MemSet(&ext, 0, sizeof(CoverExt));
	while (Cover(doc, doclen, &qr, &ext))
	{
		double		Cpos = 0.0;
		double		InvSum = 0.0;
		int			nNoise;
		DocRepresentation *ptr = ext.begin;

		while (ptr <= ext.end)
		{
			InvSum += invws[WEP_GETWEIGHT(ptr->pos)];
			ptr++;
		}

		Cpos = ((double) (ext.end - ext.begin + 1)) / InvSum;

		/*
		 * if doc are big enough then ext.q may be equal to ext.p due to limit
		 * of positional information. In this case we approximate number of
		 * noise word as half cover's length
		 */
		nNoise = (ext.q - ext.p) - (ext.end - ext.begin);
		if (nNoise < 0)
			nNoise = (ext.end - ext.begin) / 2;
		Wdoc += Cpos / ((double) (1 + nNoise));

		CurExtPos = ((double) (ext.q + ext.p)) / 2.0;
		if (NExtent > 0 && CurExtPos > PrevExtPos	/* prevent division by
													 * zero in a case of
			  * multiple lexize */ )
			SumDist += 1.0 / (CurExtPos - PrevExtPos);

		PrevExtPos = CurExtPos;
		NExtent++;
	}

	if ((method & RANK_NORM_LOGLENGTH) && txt->size > 0)
		Wdoc /= log((double) (cnt_length(txt) + 1));

	if (method & RANK_NORM_LENGTH)
	{
		len = cnt_length(txt);
		if (len > 0)
			Wdoc /= (double) len;
	}

	if ((method & RANK_NORM_EXTDIST) && NExtent > 0 && SumDist > 0)
		Wdoc /= ((double) NExtent) / SumDist;

	if ((method & RANK_NORM_UNIQ) && txt->size > 0)
		Wdoc /= (double) (txt->size);

	if ((method & RANK_NORM_LOGUNIQ) && txt->size > 0)
		Wdoc /= log((double) (txt->size + 1)) / log(2.0);

	if (method & RANK_NORM_RDIVRPLUS1)
		Wdoc /= (Wdoc + 1);

	pfree(doc);

	pfree(qr.operandData);

	return (float4) Wdoc;
}