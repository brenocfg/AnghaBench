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
typedef  scalar_t__ PFNGLWRITEMASKEXTPROC ;
typedef  scalar_t__ PFNGLVARIANTUSVEXTPROC ;
typedef  scalar_t__ PFNGLVARIANTUIVEXTPROC ;
typedef  scalar_t__ PFNGLVARIANTUBVEXTPROC ;
typedef  scalar_t__ PFNGLVARIANTSVEXTPROC ;
typedef  scalar_t__ PFNGLVARIANTPOINTEREXTPROC ;
typedef  scalar_t__ PFNGLVARIANTIVEXTPROC ;
typedef  scalar_t__ PFNGLVARIANTFVEXTPROC ;
typedef  scalar_t__ PFNGLVARIANTDVEXTPROC ;
typedef  scalar_t__ PFNGLVARIANTBVEXTPROC ;
typedef  scalar_t__ PFNGLSWIZZLEEXTPROC ;
typedef  scalar_t__ PFNGLSHADEROP3EXTPROC ;
typedef  scalar_t__ PFNGLSHADEROP2EXTPROC ;
typedef  scalar_t__ PFNGLSHADEROP1EXTPROC ;
typedef  scalar_t__ PFNGLSETLOCALCONSTANTEXTPROC ;
typedef  scalar_t__ PFNGLSETINVARIANTEXTPROC ;
typedef  scalar_t__ PFNGLISVARIANTENABLEDEXTPROC ;
typedef  scalar_t__ PFNGLINSERTCOMPONENTEXTPROC ;
typedef  scalar_t__ PFNGLGETVARIANTPOINTERVEXTPROC ;
typedef  scalar_t__ PFNGLGETVARIANTINTEGERVEXTPROC ;
typedef  scalar_t__ PFNGLGETVARIANTFLOATVEXTPROC ;
typedef  scalar_t__ PFNGLGETVARIANTBOOLEANVEXTPROC ;
typedef  scalar_t__ PFNGLGETLOCALCONSTANTINTEGERVEXTPROC ;
typedef  scalar_t__ PFNGLGETLOCALCONSTANTFLOATVEXTPROC ;
typedef  scalar_t__ PFNGLGETLOCALCONSTANTBOOLEANVEXTPROC ;
typedef  scalar_t__ PFNGLGETINVARIANTINTEGERVEXTPROC ;
typedef  scalar_t__ PFNGLGETINVARIANTFLOATVEXTPROC ;
typedef  scalar_t__ PFNGLGETINVARIANTBOOLEANVEXTPROC ;
typedef  scalar_t__ PFNGLGENVERTEXSHADERSEXTPROC ;
typedef  scalar_t__ PFNGLGENSYMBOLSEXTPROC ;
typedef  scalar_t__ PFNGLEXTRACTCOMPONENTEXTPROC ;
typedef  scalar_t__ PFNGLENDVERTEXSHADEREXTPROC ;
typedef  scalar_t__ PFNGLENABLEVARIANTCLIENTSTATEEXTPROC ;
typedef  scalar_t__ PFNGLDISABLEVARIANTCLIENTSTATEEXTPROC ;
typedef  scalar_t__ PFNGLDELETEVERTEXSHADEREXTPROC ;
typedef  scalar_t__ PFNGLBINDVERTEXSHADEREXTPROC ;
typedef  scalar_t__ PFNGLBINDTEXTUREUNITPARAMETEREXTPROC ;
typedef  scalar_t__ PFNGLBINDTEXGENPARAMETEREXTPROC ;
typedef  scalar_t__ PFNGLBINDPARAMETEREXTPROC ;
typedef  scalar_t__ PFNGLBINDMATERIALPARAMETEREXTPROC ;
typedef  scalar_t__ PFNGLBINDLIGHTPARAMETEREXTPROC ;
typedef  scalar_t__ PFNGLBEGINVERTEXSHADEREXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_EXT_vertex_shader ; 
 scalar_t__ glad_glBeginVertexShaderEXT ; 
 scalar_t__ glad_glBindLightParameterEXT ; 
 scalar_t__ glad_glBindMaterialParameterEXT ; 
 scalar_t__ glad_glBindParameterEXT ; 
 scalar_t__ glad_glBindTexGenParameterEXT ; 
 scalar_t__ glad_glBindTextureUnitParameterEXT ; 
 scalar_t__ glad_glBindVertexShaderEXT ; 
 scalar_t__ glad_glDeleteVertexShaderEXT ; 
 scalar_t__ glad_glDisableVariantClientStateEXT ; 
 scalar_t__ glad_glEnableVariantClientStateEXT ; 
 scalar_t__ glad_glEndVertexShaderEXT ; 
 scalar_t__ glad_glExtractComponentEXT ; 
 scalar_t__ glad_glGenSymbolsEXT ; 
 scalar_t__ glad_glGenVertexShadersEXT ; 
 scalar_t__ glad_glGetInvariantBooleanvEXT ; 
 scalar_t__ glad_glGetInvariantFloatvEXT ; 
 scalar_t__ glad_glGetInvariantIntegervEXT ; 
 scalar_t__ glad_glGetLocalConstantBooleanvEXT ; 
 scalar_t__ glad_glGetLocalConstantFloatvEXT ; 
 scalar_t__ glad_glGetLocalConstantIntegervEXT ; 
 scalar_t__ glad_glGetVariantBooleanvEXT ; 
 scalar_t__ glad_glGetVariantFloatvEXT ; 
 scalar_t__ glad_glGetVariantIntegervEXT ; 
 scalar_t__ glad_glGetVariantPointervEXT ; 
 scalar_t__ glad_glInsertComponentEXT ; 
 scalar_t__ glad_glIsVariantEnabledEXT ; 
 scalar_t__ glad_glSetInvariantEXT ; 
 scalar_t__ glad_glSetLocalConstantEXT ; 
 scalar_t__ glad_glShaderOp1EXT ; 
 scalar_t__ glad_glShaderOp2EXT ; 
 scalar_t__ glad_glShaderOp3EXT ; 
 scalar_t__ glad_glSwizzleEXT ; 
 scalar_t__ glad_glVariantPointerEXT ; 
 scalar_t__ glad_glVariantbvEXT ; 
 scalar_t__ glad_glVariantdvEXT ; 
 scalar_t__ glad_glVariantfvEXT ; 
 scalar_t__ glad_glVariantivEXT ; 
 scalar_t__ glad_glVariantsvEXT ; 
 scalar_t__ glad_glVariantubvEXT ; 
 scalar_t__ glad_glVariantuivEXT ; 
 scalar_t__ glad_glVariantusvEXT ; 
 scalar_t__ glad_glWriteMaskEXT ; 

__attribute__((used)) static void load_GL_EXT_vertex_shader(GLADloadproc load) {
	if(!GLAD_GL_EXT_vertex_shader) return;
	glad_glBeginVertexShaderEXT = (PFNGLBEGINVERTEXSHADEREXTPROC)load("glBeginVertexShaderEXT");
	glad_glEndVertexShaderEXT = (PFNGLENDVERTEXSHADEREXTPROC)load("glEndVertexShaderEXT");
	glad_glBindVertexShaderEXT = (PFNGLBINDVERTEXSHADEREXTPROC)load("glBindVertexShaderEXT");
	glad_glGenVertexShadersEXT = (PFNGLGENVERTEXSHADERSEXTPROC)load("glGenVertexShadersEXT");
	glad_glDeleteVertexShaderEXT = (PFNGLDELETEVERTEXSHADEREXTPROC)load("glDeleteVertexShaderEXT");
	glad_glShaderOp1EXT = (PFNGLSHADEROP1EXTPROC)load("glShaderOp1EXT");
	glad_glShaderOp2EXT = (PFNGLSHADEROP2EXTPROC)load("glShaderOp2EXT");
	glad_glShaderOp3EXT = (PFNGLSHADEROP3EXTPROC)load("glShaderOp3EXT");
	glad_glSwizzleEXT = (PFNGLSWIZZLEEXTPROC)load("glSwizzleEXT");
	glad_glWriteMaskEXT = (PFNGLWRITEMASKEXTPROC)load("glWriteMaskEXT");
	glad_glInsertComponentEXT = (PFNGLINSERTCOMPONENTEXTPROC)load("glInsertComponentEXT");
	glad_glExtractComponentEXT = (PFNGLEXTRACTCOMPONENTEXTPROC)load("glExtractComponentEXT");
	glad_glGenSymbolsEXT = (PFNGLGENSYMBOLSEXTPROC)load("glGenSymbolsEXT");
	glad_glSetInvariantEXT = (PFNGLSETINVARIANTEXTPROC)load("glSetInvariantEXT");
	glad_glSetLocalConstantEXT = (PFNGLSETLOCALCONSTANTEXTPROC)load("glSetLocalConstantEXT");
	glad_glVariantbvEXT = (PFNGLVARIANTBVEXTPROC)load("glVariantbvEXT");
	glad_glVariantsvEXT = (PFNGLVARIANTSVEXTPROC)load("glVariantsvEXT");
	glad_glVariantivEXT = (PFNGLVARIANTIVEXTPROC)load("glVariantivEXT");
	glad_glVariantfvEXT = (PFNGLVARIANTFVEXTPROC)load("glVariantfvEXT");
	glad_glVariantdvEXT = (PFNGLVARIANTDVEXTPROC)load("glVariantdvEXT");
	glad_glVariantubvEXT = (PFNGLVARIANTUBVEXTPROC)load("glVariantubvEXT");
	glad_glVariantusvEXT = (PFNGLVARIANTUSVEXTPROC)load("glVariantusvEXT");
	glad_glVariantuivEXT = (PFNGLVARIANTUIVEXTPROC)load("glVariantuivEXT");
	glad_glVariantPointerEXT = (PFNGLVARIANTPOINTEREXTPROC)load("glVariantPointerEXT");
	glad_glEnableVariantClientStateEXT = (PFNGLENABLEVARIANTCLIENTSTATEEXTPROC)load("glEnableVariantClientStateEXT");
	glad_glDisableVariantClientStateEXT = (PFNGLDISABLEVARIANTCLIENTSTATEEXTPROC)load("glDisableVariantClientStateEXT");
	glad_glBindLightParameterEXT = (PFNGLBINDLIGHTPARAMETEREXTPROC)load("glBindLightParameterEXT");
	glad_glBindMaterialParameterEXT = (PFNGLBINDMATERIALPARAMETEREXTPROC)load("glBindMaterialParameterEXT");
	glad_glBindTexGenParameterEXT = (PFNGLBINDTEXGENPARAMETEREXTPROC)load("glBindTexGenParameterEXT");
	glad_glBindTextureUnitParameterEXT = (PFNGLBINDTEXTUREUNITPARAMETEREXTPROC)load("glBindTextureUnitParameterEXT");
	glad_glBindParameterEXT = (PFNGLBINDPARAMETEREXTPROC)load("glBindParameterEXT");
	glad_glIsVariantEnabledEXT = (PFNGLISVARIANTENABLEDEXTPROC)load("glIsVariantEnabledEXT");
	glad_glGetVariantBooleanvEXT = (PFNGLGETVARIANTBOOLEANVEXTPROC)load("glGetVariantBooleanvEXT");
	glad_glGetVariantIntegervEXT = (PFNGLGETVARIANTINTEGERVEXTPROC)load("glGetVariantIntegervEXT");
	glad_glGetVariantFloatvEXT = (PFNGLGETVARIANTFLOATVEXTPROC)load("glGetVariantFloatvEXT");
	glad_glGetVariantPointervEXT = (PFNGLGETVARIANTPOINTERVEXTPROC)load("glGetVariantPointervEXT");
	glad_glGetInvariantBooleanvEXT = (PFNGLGETINVARIANTBOOLEANVEXTPROC)load("glGetInvariantBooleanvEXT");
	glad_glGetInvariantIntegervEXT = (PFNGLGETINVARIANTINTEGERVEXTPROC)load("glGetInvariantIntegervEXT");
	glad_glGetInvariantFloatvEXT = (PFNGLGETINVARIANTFLOATVEXTPROC)load("glGetInvariantFloatvEXT");
	glad_glGetLocalConstantBooleanvEXT = (PFNGLGETLOCALCONSTANTBOOLEANVEXTPROC)load("glGetLocalConstantBooleanvEXT");
	glad_glGetLocalConstantIntegervEXT = (PFNGLGETLOCALCONSTANTINTEGERVEXTPROC)load("glGetLocalConstantIntegervEXT");
	glad_glGetLocalConstantFloatvEXT = (PFNGLGETLOCALCONSTANTFLOATVEXTPROC)load("glGetLocalConstantFloatvEXT");
}