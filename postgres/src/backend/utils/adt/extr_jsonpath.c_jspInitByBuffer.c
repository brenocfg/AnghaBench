#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int int32 ;
struct TYPE_13__ {int first; int last; } ;
struct TYPE_12__ {int nelems; int /*<<< orphan*/  elems; } ;
struct TYPE_11__ {int flags; int expr; int patternlen; char* pattern; } ;
struct TYPE_10__ {int left; int right; } ;
struct TYPE_9__ {int datalen; char* data; } ;
struct TYPE_14__ {int arg; TYPE_5__ anybounds; TYPE_4__ array; TYPE_3__ like_regex; TYPE_2__ args; TYPE_1__ value; } ;
struct TYPE_15__ {char* base; int type; int nextPos; TYPE_6__ content; } ;
typedef  TYPE_7__ JsonPathItem ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int INTALIGN (uintptr_t) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
#define  jpiAbs 169 
#define  jpiAdd 168 
#define  jpiAnd 167 
#define  jpiAny 166 
#define  jpiAnyArray 165 
#define  jpiAnyKey 164 
#define  jpiBool 163 
#define  jpiCeiling 162 
#define  jpiCurrent 161 
#define  jpiDatetime 160 
#define  jpiDiv 159 
#define  jpiDouble 158 
#define  jpiEqual 157 
#define  jpiExists 156 
#define  jpiFilter 155 
#define  jpiFloor 154 
#define  jpiGreater 153 
#define  jpiGreaterOrEqual 152 
#define  jpiIndexArray 151 
#define  jpiIsUnknown 150 
#define  jpiKey 149 
#define  jpiKeyValue 148 
#define  jpiLast 147 
#define  jpiLess 146 
#define  jpiLessOrEqual 145 
#define  jpiLikeRegex 144 
#define  jpiMinus 143 
#define  jpiMod 142 
#define  jpiMul 141 
#define  jpiNot 140 
#define  jpiNotEqual 139 
#define  jpiNull 138 
#define  jpiNumeric 137 
#define  jpiOr 136 
#define  jpiPlus 135 
#define  jpiRoot 134 
#define  jpiSize 133 
#define  jpiStartsWith 132 
#define  jpiString 131 
#define  jpiSub 130 
#define  jpiType 129 
#define  jpiVariable 128 
 int /*<<< orphan*/  read_byte (int,char*,int) ; 
 int /*<<< orphan*/  read_int32 (int,char*,int) ; 
 int /*<<< orphan*/  read_int32_n (int /*<<< orphan*/ ,char*,int,int) ; 

void
jspInitByBuffer(JsonPathItem *v, char *base, int32 pos)
{
	v->base = base + pos;

	read_byte(v->type, base, pos);
	pos = INTALIGN((uintptr_t) (base + pos)) - (uintptr_t) base;
	read_int32(v->nextPos, base, pos);

	switch (v->type)
	{
		case jpiNull:
		case jpiRoot:
		case jpiCurrent:
		case jpiAnyArray:
		case jpiAnyKey:
		case jpiType:
		case jpiSize:
		case jpiAbs:
		case jpiFloor:
		case jpiCeiling:
		case jpiDouble:
		case jpiKeyValue:
		case jpiLast:
			break;
		case jpiKey:
		case jpiString:
		case jpiVariable:
			read_int32(v->content.value.datalen, base, pos);
			/* FALLTHROUGH */
		case jpiNumeric:
		case jpiBool:
			v->content.value.data = base + pos;
			break;
		case jpiAnd:
		case jpiOr:
		case jpiAdd:
		case jpiSub:
		case jpiMul:
		case jpiDiv:
		case jpiMod:
		case jpiEqual:
		case jpiNotEqual:
		case jpiLess:
		case jpiGreater:
		case jpiLessOrEqual:
		case jpiGreaterOrEqual:
		case jpiStartsWith:
			read_int32(v->content.args.left, base, pos);
			read_int32(v->content.args.right, base, pos);
			break;
		case jpiLikeRegex:
			read_int32(v->content.like_regex.flags, base, pos);
			read_int32(v->content.like_regex.expr, base, pos);
			read_int32(v->content.like_regex.patternlen, base, pos);
			v->content.like_regex.pattern = base + pos;
			break;
		case jpiNot:
		case jpiExists:
		case jpiIsUnknown:
		case jpiPlus:
		case jpiMinus:
		case jpiFilter:
		case jpiDatetime:
			read_int32(v->content.arg, base, pos);
			break;
		case jpiIndexArray:
			read_int32(v->content.array.nelems, base, pos);
			read_int32_n(v->content.array.elems, base, pos,
						 v->content.array.nelems * 2);
			break;
		case jpiAny:
			read_int32(v->content.anybounds.first, base, pos);
			read_int32(v->content.anybounds.last, base, pos);
			break;
		default:
			elog(ERROR, "unrecognized jsonpath item type: %d", v->type);
	}
}