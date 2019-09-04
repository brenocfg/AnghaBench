#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  index_sizes ;
struct TYPE_22__ {int /*<<< orphan*/  VirtualAddress; } ;
struct TYPE_28__ {TYPE_1__ Resources; } ;
struct TYPE_27__ {scalar_t__ data; } ;
struct TYPE_26__ {TYPE_2__* tilde; } ;
struct TYPE_25__ {int HeapSizes; int Valid; } ;
struct TYPE_24__ {int string; int guid; int blob; int moduleref; int assemblyref; int assemblyrefprocessor; int methoddef; int memberref; int typedef_; int field; int param; int property; int event; int genericparam; void* methodspec; void* genericparamconstraint; void* manifestresource; void* exportedtype; void* file; void* assembly; void* standalonesig; void* interfaceimpl; void* typespec; void* typeref; void* module; } ;
struct TYPE_23__ {scalar_t__ Offset; } ;
typedef  TYPE_3__ ROWS ;
typedef  TYPE_4__* PTILDE_HEADER ;
typedef  TYPE_5__* PSTREAMS ;
typedef  TYPE_6__ PE ;
typedef  TYPE_7__* PCLI_HEADER ;
typedef  TYPE_3__ INDEX_SIZES ;

/* Variables and functions */
#define  BIT_ASSEMBLY 149 
#define  BIT_ASSEMBLYREF 148 
#define  BIT_ASSEMBLYREFPROCESSOR 147 
#define  BIT_EVENT 146 
#define  BIT_EXPORTEDTYPE 145 
#define  BIT_FIELD 144 
#define  BIT_FILE 143 
#define  BIT_GENERICPARAM 142 
#define  BIT_GENERICPARAMCONSTRAINT 141 
#define  BIT_INTERFACEIMPL 140 
#define  BIT_MANIFESTRESOURCE 139 
#define  BIT_MEMBERREF 138 
#define  BIT_METHODDEF 137 
#define  BIT_METHODSPEC 136 
#define  BIT_MODULE 135 
#define  BIT_MODULEREF 134 
#define  BIT_PARAM 133 
#define  BIT_PROPERTY 132 
#define  BIT_STANDALONESIG 131 
#define  BIT_TYPEDEF 130 
#define  BIT_TYPEREF 129 
#define  BIT_TYPESPEC 128 
 int /*<<< orphan*/  TILDE_HEADER ; 
 int /*<<< orphan*/  dotnet_parse_tilde_2 (TYPE_6__*,TYPE_4__*,scalar_t__,scalar_t__,TYPE_3__,TYPE_3__,TYPE_5__*) ; 
 int /*<<< orphan*/  fits_in_pe (TYPE_6__*,void**,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int,int) ; 
 scalar_t__ pe_rva_to_offset (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  struct_fits_in_pe (TYPE_6__*,TYPE_4__*,int /*<<< orphan*/ ) ; 

void dotnet_parse_tilde(
    PE* pe,
    ut64 metadata_root,
    PCLI_HEADER cli_header,
    PSTREAMS streams)
{
  PTILDE_HEADER tilde_header;
  ut64 resource_base;
  uint32_t* row_offset = NULL;

  int bit_check;

  // This is used as an offset into the rows and tables. For every bit set in
  // Valid this will be incremented. This is because the bit position doesn't
  // matter, just the number of bits that are set, when determining how many
  // rows and what the table structure is.
  int matched_bits = 0;

  // We need to know the number of rows for some tables, because they are
  // indexed into. The index will be either 2 or 4 bytes, depending upon the
  // number of rows being indexed into.
  ROWS rows;
  INDEX_SIZES index_sizes;

  // Default all rows to 0. They will be set to actual values later on, if
  // they exist in the file.
  memset(&rows, '\0', sizeof(ROWS));

  // Default index sizes are 2. Will be bumped to 4 if necessary.
  memset(&index_sizes, 2, sizeof(index_sizes));

  tilde_header = (PTILDE_HEADER) (
      pe->data +
      metadata_root +
      streams->tilde->Offset);

  if (!struct_fits_in_pe(pe, tilde_header, TILDE_HEADER))
    return;

  // Set index sizes for various heaps.
  if (tilde_header->HeapSizes & 0x01)
    index_sizes.string = 4;
  if (tilde_header->HeapSizes & 0x02)
    index_sizes.guid = 4;
  if (tilde_header->HeapSizes & 0x04)
    index_sizes.blob = 4;

  // Immediately after the tilde header is an array of 32bit values which
  // indicate how many rows are in each table. The tables are immediately
  // after the rows array.
  //
  // Save the row offset.
  row_offset = (uint32_t*) (tilde_header + 1);

  // Walk all the bits first because we need to know the number of rows for
  // some tables in order to parse others. In particular this applies to
  // coded indexes, which are documented in ECMA-335 II.24.2.6.
  for (bit_check = 0; bit_check < 64; bit_check++)
  {
    if (!((tilde_header->Valid >> bit_check) & 0x01))
      continue;

#define ROW_CHECK(name) \
    if (fits_in_pe(pe, row_offset, (matched_bits + 1) * sizeof(uint32_t))) \
      rows.name = *(row_offset + matched_bits);

#define ROW_CHECK_WITH_INDEX(name) \
    ROW_CHECK(name); \
    if (rows.name > 0xFFFF) \
      index_sizes.name = 4;

    switch (bit_check)
    {
      case BIT_MODULE:
        ROW_CHECK(module);
        break;
      case BIT_MODULEREF:
        ROW_CHECK_WITH_INDEX(moduleref);
        break;
      case BIT_ASSEMBLYREF:
        ROW_CHECK_WITH_INDEX(assemblyref);
        break;
      case BIT_ASSEMBLYREFPROCESSOR:
        ROW_CHECK_WITH_INDEX(assemblyrefprocessor);
        break;
      case BIT_TYPEREF:
        ROW_CHECK(typeref);
        break;
      case BIT_METHODDEF:
        ROW_CHECK_WITH_INDEX(methoddef);
        break;
      case BIT_MEMBERREF:
        ROW_CHECK_WITH_INDEX(memberref);
        break;
      case BIT_TYPEDEF:
        ROW_CHECK_WITH_INDEX(typedef_);
        break;
      case BIT_TYPESPEC:
        ROW_CHECK(typespec);
        break;
      case BIT_FIELD:
        ROW_CHECK_WITH_INDEX(field);
        break;
      case BIT_PARAM:
        ROW_CHECK_WITH_INDEX(param);
        break;
      case BIT_PROPERTY:
        ROW_CHECK_WITH_INDEX(property);
        break;
      case BIT_INTERFACEIMPL:
        ROW_CHECK(interfaceimpl);
        break;
      case BIT_EVENT:
        ROW_CHECK_WITH_INDEX(event);
        break;
      case BIT_STANDALONESIG:
        ROW_CHECK(standalonesig);
        break;
      case BIT_ASSEMBLY:
        ROW_CHECK(assembly);
        break;
      case BIT_FILE:
        ROW_CHECK(file);
        break;
      case BIT_EXPORTEDTYPE:
        ROW_CHECK(exportedtype);
        break;
      case BIT_MANIFESTRESOURCE:
        ROW_CHECK(manifestresource);
        break;
      case BIT_GENERICPARAM:
        ROW_CHECK_WITH_INDEX(genericparam);
        break;
      case BIT_GENERICPARAMCONSTRAINT:
        ROW_CHECK(genericparamconstraint);
        break;
      case BIT_METHODSPEC:
        ROW_CHECK(methodspec);
        break;
      default:
        break;
    }

    matched_bits++;
  }

  // This is used when parsing the MANIFEST RESOURCE table.
  resource_base = pe_rva_to_offset(pe, cli_header->Resources.VirtualAddress);

  dotnet_parse_tilde_2(
      pe,
      tilde_header,
      resource_base,
      metadata_root,
      rows,
      index_sizes,
      streams);
}