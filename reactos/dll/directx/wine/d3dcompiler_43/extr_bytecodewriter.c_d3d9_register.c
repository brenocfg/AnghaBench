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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ BWRITERSPR_ADDR ; 
 scalar_t__ BWRITERSPR_ATTROUT ; 
 scalar_t__ BWRITERSPR_COLOROUT ; 
 scalar_t__ BWRITERSPR_CONST ; 
 scalar_t__ BWRITERSPR_CONSTBOOL ; 
 scalar_t__ BWRITERSPR_CONSTINT ; 
 scalar_t__ BWRITERSPR_DEPTHOUT ; 
 scalar_t__ BWRITERSPR_INPUT ; 
 scalar_t__ BWRITERSPR_LABEL ; 
 scalar_t__ BWRITERSPR_LOOP ; 
 scalar_t__ BWRITERSPR_MISCTYPE ; 
 scalar_t__ BWRITERSPR_OUTPUT ; 
 scalar_t__ BWRITERSPR_PREDICATE ; 
 scalar_t__ BWRITERSPR_RASTOUT ; 
 scalar_t__ BWRITERSPR_SAMPLER ; 
 scalar_t__ BWRITERSPR_TEMP ; 
 scalar_t__ BWRITERSPR_TEXCRDOUT ; 
 scalar_t__ BWRITERSPR_TEXTURE ; 
 scalar_t__ D3DSPR_ADDR ; 
 scalar_t__ D3DSPR_ATTROUT ; 
 scalar_t__ D3DSPR_COLOROUT ; 
 scalar_t__ D3DSPR_CONST ; 
 scalar_t__ D3DSPR_CONSTBOOL ; 
 scalar_t__ D3DSPR_CONSTINT ; 
 scalar_t__ D3DSPR_DEPTHOUT ; 
 scalar_t__ D3DSPR_INPUT ; 
 scalar_t__ D3DSPR_LABEL ; 
 scalar_t__ D3DSPR_LOOP ; 
 scalar_t__ D3DSPR_MISCTYPE ; 
 scalar_t__ D3DSPR_OUTPUT ; 
 scalar_t__ D3DSPR_PREDICATE ; 
 scalar_t__ D3DSPR_RASTOUT ; 
 scalar_t__ D3DSPR_SAMPLER ; 
 scalar_t__ D3DSPR_TEMP ; 
 scalar_t__ D3DSPR_TEXCRDOUT ; 
 scalar_t__ D3DSPR_TEXTURE ; 
 int /*<<< orphan*/  FIXME (char*,scalar_t__) ; 

__attribute__((used)) static DWORD d3d9_register(DWORD bwriter_register)
{
    if (bwriter_register == BWRITERSPR_TEMP)        return D3DSPR_TEMP;
    if (bwriter_register == BWRITERSPR_INPUT)       return D3DSPR_INPUT;
    if (bwriter_register == BWRITERSPR_CONST)       return D3DSPR_CONST;
    if (bwriter_register == BWRITERSPR_ADDR)        return D3DSPR_ADDR;
    if (bwriter_register == BWRITERSPR_TEXTURE)     return D3DSPR_TEXTURE;
    if (bwriter_register == BWRITERSPR_RASTOUT)     return D3DSPR_RASTOUT;
    if (bwriter_register == BWRITERSPR_ATTROUT)     return D3DSPR_ATTROUT;
    if (bwriter_register == BWRITERSPR_TEXCRDOUT)   return D3DSPR_TEXCRDOUT;
    if (bwriter_register == BWRITERSPR_OUTPUT)      return D3DSPR_OUTPUT;
    if (bwriter_register == BWRITERSPR_CONSTINT)    return D3DSPR_CONSTINT;
    if (bwriter_register == BWRITERSPR_COLOROUT)    return D3DSPR_COLOROUT;
    if (bwriter_register == BWRITERSPR_DEPTHOUT)    return D3DSPR_DEPTHOUT;
    if (bwriter_register == BWRITERSPR_SAMPLER)     return D3DSPR_SAMPLER;
    if (bwriter_register == BWRITERSPR_CONSTBOOL)   return D3DSPR_CONSTBOOL;
    if (bwriter_register == BWRITERSPR_LOOP)        return D3DSPR_LOOP;
    if (bwriter_register == BWRITERSPR_MISCTYPE)    return D3DSPR_MISCTYPE;
    if (bwriter_register == BWRITERSPR_LABEL)       return D3DSPR_LABEL;
    if (bwriter_register == BWRITERSPR_PREDICATE)   return D3DSPR_PREDICATE;

    FIXME("Unexpected BWRITERSPR %#x.\n", bwriter_register);
    return ~0U;
}